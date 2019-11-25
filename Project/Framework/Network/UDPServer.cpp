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
#include "../../source/Viewer/UDPServerViewer.h"
#include "../../source/Viewer/EventLiveViewer.h"
#include "../../source/Viewer/Background.h"
#include "../../source/Viewer/Transition.h"

#include "../Input/input.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
HANDLE UDPServer::Thread;

//=============================================================================
// コンストラクタ
//=============================================================================
UDPServer::UDPServer() :
	Current(State::Ranking)
{
	background = new Background();
	//RankingViewer = new UDPServerViewer();
	transition = new Transition();

	ViewerContainer.resize(State::Max);
	ViewerContainer[State::Ranking] = new UDPServerViewer();
	ViewerContainer[State::Event] = new EventLiveViewer();

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
	//SAFE_DELETE(EventViewer);
	//SAFE_DELETE(RankingViewer);
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

	if (Keyboard::GetTrigger(DIK_F))
	{
		CreateViewerTexture();
		transition->SetTransition();
		Current = State::Event;
	}
	if (Keyboard::GetTrigger(DIK_G))
	{
		Current = State::Ranking;
	}
	if (Keyboard::GetTrigger(DIK_D))
	{
		vector<string> Test;
		Test.push_back("これはLink専用の通信パケットです");
		Test.push_back("1");
		Test.push_back("Potato");
		Test.push_back("118486132189");
		RankStack.push_back(Test);
	}
#endif

	if (Current == State::Ranking)
	{
		if (!RankStack.empty())
		{
			for (auto &Str : RankStack)
			{
				int Type = stoi(Str.at(Packet::Rank::Type));
				ViewerContainer.at(Current)->ReceivePacket(Type, Str);
				//RankingViewer->CreateRankViewer(Str.at(0), Str.at(1));
				Str.clear();
			}
			RankStack.clear();
		}
	}

	background->Update();

	transition->Update();

	ViewerContainer.at(Current)->Update();
	//RankingViewer->Update();

}


//=============================================================================
// ランキング描画
//=============================================================================
void UDPServer::DrawRanking()
{
	if (!transition->InActive())
	{
		ViewerContainer.at(Current)->Draw();
		//RankingViewer->Draw();
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
			RankStack.push_back(SplitedStr);
		}
	}
}

void UDPServer::CreateViewerTexture(void)
{
	LPDIRECT3DSURFACE9 OldSurface;
	LPDIRECT3DSURFACE9 RenderSurface;
	static LPDIRECT3DTEXTURE9 RenderTexture;
	LPDIRECT3DDEVICE9 Device = GetDevice();
	const D3DXCOLOR BackColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//レンダーテクスチャ作成
	Device->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&RenderTexture,
		0);

	RenderTexture->GetSurfaceLevel(0, &RenderSurface);

	//レンダーターゲット切り替え
	Device->GetRenderTarget(0, &OldSurface);
	Device->SetRenderTarget(0, RenderSurface);
	Device->Clear(0, NULL, D3DCLEAR_TARGET, BackColor, 1.0f, 0);

	ViewerContainer.at(State::Ranking)->Draw();

	//レンダーターゲット復元
	Device->SetRenderTarget(0, OldSurface);
	SAFE_RELEASE(OldSurface);
	SAFE_RELEASE(RenderSurface);

	transition->LoadTexture(RenderTexture);
	RenderTexture = nullptr;
}
