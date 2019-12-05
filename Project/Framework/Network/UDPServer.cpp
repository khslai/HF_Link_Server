//=============================================================================
//
// UDPサーバークラス [UDPServer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "UDPServer.h"
#include "PacketConfig.h"
#include "../String/String.h"
#include "../Tool/DebugWindow.h"
#include "../Task/TaskManager.h"
#include "../Input/input.h"
#include "../../source/Viewer/RankingViewer.h"
#include "../../source/Viewer/EventLiveViewer.h"
#include "../../source/Viewer/LevelUpViewer.h"
#include "../../source/Viewer/Background.h"
#include "../../source/Transition/Transition.h"
#include "../../source/Viewer/ViewerConfig.h"
#include "../../source/Effect/GameParticleManager.h"
#include "../../source/EventConfig.h"


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
HANDLE UDPServer::Thread;

//=============================================================================
// コンストラクタ
//=============================================================================
UDPServer::UDPServer() :
	Current(Viewer::State::Ranking),
	InIdle(true)
{
	background = new Background();
	transition = new Transition();

	ViewerContainer.resize(Viewer::State::Max);
	ViewerContainer[Viewer::State::Ranking] = new RankingViewer([&](bool Flag) {SetIdle(Flag); });
	ViewerContainer[Viewer::State::EventLive] = new EventLiveViewer([&]() {RankingRecovery(); });
	ViewerContainer[Viewer::State::LevelUp] = new LevelUpViewer([&]() {RankingRecovery(); });

	// WinSock初期化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ソケット生成
	ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// 受信アドレスとポート番号
	sockaddr_in ServerAddress;
	ServerAddress.sin_port = htons(ServerPort);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = INADDR_ANY;

	// ソケットに名前を付ける
	// "::"がないとbindのオーバーロードのstd::bindが呼び出される
	::bind(ServerSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPServer::~UDPServer()
{
	// メモリ解放
	SAFE_DELETE(background);
	SAFE_DELETE(transition);
	Utility::DeleteContainer(ViewerContainer);
	ConnectedList.clear();
	RankStack.clear();
	EventStack.clear();

	// WinSock終了処理
	closesocket(ServerSocket);
	WSACleanup();

	// ===============================================================
	// 注意。きちんとスレッド終了関数(_endthreadex)を呼ばないと
	// メインスレッドが終了した後に他のスレッドはそのまま実行します
	// 例外スローの可能性が高い
	// ===============================================================
	// スレッドが解放するまで待つ
	DWORD ThreadResult = WaitForSingleObject(Thread, INFINITE);
	if (ThreadResult == WAIT_OBJECT_0)
	{
		// スレッド終了
		CloseHandle(Thread);
	}
}

//=============================================================================
// 更新
//=============================================================================
void UDPServer::Update(void)
{
#if _DEBUG
	Debug();
#endif

	// パケットを処理
	PacketProcess();

	background->Update();

	transition->Update();

	ViewerContainer.at(Current)->Update();
}


//=============================================================================
// ランキング描画
//=============================================================================
void UDPServer::DrawRanking()
{
	if (!transition->InActive())
	{
		ViewerContainer.at(Current)->Draw();
	}
	else
	{
		transition->Draw();
	}
}

//=============================================================================
// 背景描画
//=============================================================================
void UDPServer::DrawBackground(void)
{
	background->Draw();
}

//=============================================================================
// 受信スレッド(マルチスレッド用)
//=============================================================================
unsigned __stdcall UDPServer::ThreadEntryPoint(void* This)
{
	UDPServer* Temp = (UDPServer*)This;
	Temp->ReceivePacket();					// 本当のセカンドスレッドの処理関数
	_endthreadex(0);						// スレッドの実行停止
	return 0;
}

//=============================================================================
// 受信スレッド
// できる限り、マルチスレッドの関数に長い時間がかかる処理を書かないように
// どうしても処理時間が必要そうな場合、WaitForSingleObjectの待つ時間を長くして
//=============================================================================
void UDPServer::ReceivePacket(void)
{
	// データ受信
	char data[256];
	int AddressLength;
	sockaddr_in FromAddress;

	while (true)
	{
		AddressLength = sizeof(FromAddress);

		// 文字列のクリア
		memset(data, 0, sizeof(data));

		// メッセージ受信
		recvfrom(ServerSocket, (char*)data, sizeof(data), 0, (sockaddr*)&FromAddress, &AddressLength);

		// ServerSocketが閉じた後にrecvfromは飛ばされるので
		// 無限ループから出るための条件式は必要
		if (strcmp(data, "") == 0)
		{
			break;
		}

#if _DEBUG
		// 送信元のIPアドレスが既にリストの中かどうかを確認
		bool Existed = false;
		for (auto &Address : ConnectedList)
		{
			if (Address.sin_port == FromAddress.sin_port &&
				strcmp(inet_ntoa(Address.sin_addr), inet_ntoa(FromAddress.sin_addr)) == 0)
			{
				Existed = true;
				break;
			}
		}

		// 接続リストに新しいクライアントを追加
		if (!Existed)
		{
			ConnectedList.push_back(FromAddress);
		}
#endif

		string Message = data;
		// 受信した文字列を分割
		std::vector<string> SplitedStr;
		String::Split(SplitedStr, Message, ',');

		// パケットのヘッダーを確認
		if (SplitedStr.at(Packet::Header) == "これはLink専用の通信パケットです")
		{
			int Type = stoi(SplitedStr.at(Packet::Type));

			if (Type == Packet::InsertRank)
			{
				// スタックに表示予定のランクを追加
				RankStack.push_back(SplitedStr);
			}
			else if (Type == Packet::EventLive || Type == Packet::LevelUp)
			{
				if (InIdle && Current == Viewer::Ranking)
				{
					// スタックに表示予定のイベントを追加
					EventStack.push_back(SplitedStr);
				}
			}
			else if (Type == Packet::GetLastScore)
			{
				string Score = ((RankingViewer*)ViewerContainer.at(Viewer::Ranking))->GetLastScore();

				sendto(ServerSocket, Score.c_str(), Score.length() + 1, 0, (sockaddr*)&FromAddress, sizeof(FromAddress));
			}
		}
	}
}

//=============================================================================
// クライアントに最下位のスコアを送る
//=============================================================================
void UDPServer::SendLastScore(void)
{
	string Score = ((RankingViewer*)ViewerContainer.at(Viewer::Ranking))->GetLastScore();
}

//=============================================================================
// パケットのを処理する
//=============================================================================
void UDPServer::PacketProcess(void)
{
	// 待機状態であれば
	if (InIdle && Current == Viewer::Ranking)
	{
		// 処理待ちのパケットがあれば
		if (!RankStack.empty())
		{
			// 先にランキング追加の事件を処理
			for (auto &Str : RankStack)
			{
				int Type = stoi(Str.at(Packet::Type));
				if (Type == Packet::InsertRank)
				{
					InIdle = false;
					ViewerContainer.at(Viewer::Ranking)->ReceivePacket(Type, Str);
				}
				Str.clear();
			}
			RankStack.clear();
		}
		// イベントパケット処理
		else
		{
			if (!EventStack.empty())
			{
				for (auto &Str : EventStack)
				{
					int Type = stoi(Str.at(Packet::Type));

					// イベント中継
					if (Type == Packet::EventLive)
					{
						GameParticleManager::Instance()->SetGlassShards();
						TaskManager::Instance()->CreateDelayedTask(60, [=]()
						{
							ChangeViewer(Viewer::EventLive, 0, [=]()
							{
								ViewerContainer.at(Viewer::EventLive)->ReceivePacket(Type, Str);
							});
						});
						Str.clear();
						EventStack.clear();
						break;
					}
					// フィールドレベルアップ
					else if (Type == Packet::LevelUp)
					{
						GameParticleManager::Instance()->SetGlassShards();
						TaskManager::Instance()->CreateDelayedTask(60, [=]()
						{
							ChangeViewer(Viewer::LevelUp, 0, [=]()
							{
								ViewerContainer.at(Viewer::LevelUp)->ReceivePacket(Type, Str);
							});
						});
						Str.clear();
						EventStack.clear();
						break;
					}
				}
			}
		}
	}
}

//=============================================================================
// ビューアを変える
//=============================================================================
void UDPServer::ChangeViewer(int NextViewer, int TransitionType, std::function<void(void)> Callback)
{
	LPDIRECT3DTEXTURE9 ViewerTexture = nullptr;

	((RankingViewer*)ViewerContainer.at(Viewer::State::Ranking))->CreateViewerTex(&ViewerTexture);
	transition->SetTransition(TransitionType, ViewerTexture);
	background->SetBGTransition(NextViewer);

	TaskManager::Instance()->CreateDelayedTask(60, [=]()
	{
		Current = NextViewer;
		if (Callback != nullptr)
			Callback();
	});
}

//=============================================================================
// ランキングの復帰
//=============================================================================
void UDPServer::RankingRecovery(void)
{
	background->SetBGTransition(Viewer::State::Ranking);

	TaskManager::Instance()->CreateDelayedTask(60, [=]()
	{
		Current = Viewer::State::Ranking;
		((RankingViewer*)ViewerContainer.at(Viewer::State::Ranking))->RankingRecovery();
	});
}

#if _DEBUG
void UDPServer::Debug(void)
{
	Debug::Begin("UDP Server's Clients");
	for (auto &Client : ConnectedList)
	{
		Debug::Text("IP Address:%s", inet_ntoa(Client.sin_addr));
		Debug::Text("Port:%d", Client.sin_port);
		Debug::NewLine();
	}
	Debug::End();

	Debug::Begin("EventPacket");
	std::vector<string> EventPacketTemp;
	EventPacketTemp.resize(Packet::Max);
	EventPacketTemp.at(Packet::Header) = "これはLink専用の通信パケットです";
	if (Debug::Button("NewCity_City"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::NewCity);
		EventPacketTemp.at(Packet::FieldLevel) = std::to_string(FieldLevel::City);
	}
	else if (Debug::Button("NewCity_World"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::NewCity);
		EventPacketTemp.at(Packet::FieldLevel) = std::to_string(FieldLevel::World);
	}
	else if (Debug::Button("NewCity_Space"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::NewCity);
		EventPacketTemp.at(Packet::FieldLevel) = std::to_string(FieldLevel::Space);
	}
	else if (Debug::Button("Meteor"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::CityDestroy);
	}
	else if (Debug::Button("AIStrike"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::BanStockUse);
	}
	else if (Debug::Button("UFO"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::AILevelDecrease);
	}
	else if (Debug::Button("LevelUp"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::LevelUp);
	}

	if (!EventPacketTemp.at(Packet::Type).empty())
		EventStack.push_back(EventPacketTemp);
	Debug::End();

	Debug::Begin("RankPacket");
	std::vector<string> RankPacketTemp;
	RankPacketTemp.resize(Packet::Max);
	RankPacketTemp.at(Packet::Header) = "これはLink専用の通信パケットです";
	RankPacketTemp.at(Packet::Type) = std::to_string(Packet::InsertRank);
	if (Debug::Button("123"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "123";
	}
	else if (Debug::Button("000000"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "000000";
	}
	else if (Debug::Button("001230"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "001230";
	}
	else if (Debug::Button("456789"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "456789";
	}
	else if (Debug::Button("123456789101"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "123456789101";
	}
	else if (Debug::Button("999999999999"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "999999999999";
	}
	else if (Debug::Button("2131874613284489"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "2131874613284489";
	}

	if (!RankPacketTemp.at(Packet::PlayerName).empty())
		RankStack.push_back(RankPacketTemp);
	Debug::End();
}
#endif