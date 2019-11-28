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
#include "../../source/Viewer/Background.h"
#include "../../source/Viewer/Transition.h"
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
	Current(Viewer::State::Ranking)
{
	background = new Background();
	transition = new Transition();

	ViewerContainer.resize(Viewer::State::Max);
	ViewerContainer[Viewer::State::Ranking] = new RankingViewer();
	ViewerContainer[Viewer::State::EventLive] = new EventLiveViewer();

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
	bind(ServerSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
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
	Debug::Begin("UDP Server's Clients");
	for (auto &Client : ConnectedList)
	{
		Debug::Text("IP Address:%s", inet_ntoa(Client.sin_addr));
		Debug::Text("Port:%d", Client.sin_port);
		Debug::NewLine();
	}
	Debug::End();

	Debug::Begin("ReceivePacket");
	std::vector<string> Packet;
	Packet.resize(Packet::Max);
	Packet.at(Packet::Header) = "これはLink専用の通信パケットです";
	if (Debug::Button("RankInsert"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::InsertRank);
		Packet.at(Packet::PlayerName) = "Player";
		Packet.at(Packet::AILevel) = "123456654321";
	}
	else if (Debug::Button("NewCity"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::NewCity;
	}
	else if (Debug::Button("Meteor"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::CityDestroy;
	}
	else if (Debug::Button("AIStrike"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::BanStockUse;
	}
	else if (Debug::Button("UFO"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::AILevelDecrease;
	}

	if (!Packet.at(Packet::Type).empty())
		PacketStack.push_back(Packet);

	Debug::End();

	Debug::Begin("ViewerChange");
	if (Debug::Button("EventViewer"))
	{
		// エフェクト
		GameParticleManager::Instance()->SetGlassShards();
		TaskManager::Instance()->CreateDelayedTask(60, [&]()
		{
			ChangeViewer(Viewer::State::EventLive, 0);
		});
	}
	else if (Debug::Button("RankingViewer"))
	{
		ChangeViewer(Viewer::State::Ranking, 0);
		//background->RecoveryBGColor();
		//Current = Viewer::State::Ranking;
	}
	Debug::End();

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
		if (SplitedStr.at(0) == "これはLink専用の通信パケットです")
		{
			//SplitedStr.erase(SplitedStr.begin());

			// スタックに表示予定のオブジェクトを追加
			PacketStack.push_back(SplitedStr);
		}
	}
}

//=============================================================================
// パケットのを処理する
//=============================================================================
void UDPServer::PacketProcess(void)
{
	// 処理待ちのパケットがあれば
	if (!PacketStack.empty() && !InInsertRank)
	{
		// 先にランキング追加の事件を処理
		for (auto &Str : PacketStack)
		{
			int Type = stoi(Str.at(Packet::Type));
			if (Type == Packet::InsertRank)
			{
				InInsertRank = true;
				ViewerContainer.at(Viewer::Ranking)->ReceivePacket(Type, Str);
			}
			Str.clear();
		}

		// 後に他の事件を処理
		if (!InInsertRank)
		{
			for (auto &Str : PacketStack)
			{
				if (Str.empty())
					continue;

				int Type = stoi(Str.at(Packet::Type));
				if (Type == Packet::EventLive)
				{
					ViewerContainer.at(Viewer::EventLive)->ReceivePacket(Type, Str);
				}
				else if (Type == Packet::LevelUp)
				{
					//ViewerContainer.at(Viewer::)->ReceivePacket(Type, Str);
				}
				Str.clear();
			}
		}
	}

	// 空きパケットを削除
	PacketStack.erase(std::remove_if(std::begin(PacketStack), std::end(PacketStack), [](vector<string> Packet)
	{
		return Packet.empty();
	}), std::end(PacketStack));
}

//=============================================================================
// ビューアを変える
//=============================================================================
void UDPServer::ChangeViewer(int NextViewer, int TransitionType)
{
	LPDIRECT3DTEXTURE9 ViewerTexture = nullptr;

	ViewerContainer.at(Viewer::State::Ranking)->CreateViewerTex(&ViewerTexture);
	transition->SetTransition(TransitionType, ViewerTexture);
	background->SetBGTransition(NextViewer);
	Current = NextViewer;
}
