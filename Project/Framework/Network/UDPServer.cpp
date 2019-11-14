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



//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
HANDLE UDPServer::Thread;

//=============================================================================
// コンストラクタ
//=============================================================================
UDPServer::UDPServer()
{
	Viewer = new UDPServerViewer();

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
	SAFE_DELETE(Viewer);
	ConnectedList.clear();

	// スレッド解放
	CloseHandle(Thread);

	// WinSock終了処理
	closesocket(ServerSocket);
	WSACleanup();
}

//=============================================================================
// 更新
//=============================================================================
void UDPServer::Update(void)
{
	Debug::Begin("UDP Server's Clients");
	for (auto &Client : ConnectedList)
	{
		Debug::Text("IP Address:%s", inet_ntoa(Client.sin_addr));
		Debug::Text("Port:%d", Client.sin_port);
		Debug::NewLine();
	}
	Debug::End();

	Debug::Begin("Ranking Test");
	if (Debug::Button("Clear"))
		Viewer->ClearRanking();
	else if (Debug::Button("123"))
		Viewer->CreateRankViewer("Player", "123");
	else if (Debug::Button("123455"))
		Viewer->CreateRankViewer("Player", "123455");
	else if (Debug::Button("123456"))
		Viewer->CreateRankViewer("Player", "123456");
	else if (Debug::Button("123457"))
		Viewer->CreateRankViewer("Player", "123457");
	else if (Debug::Button("123456789"))
		Viewer->CreateRankViewer("Player", "123456789");
	else if (Debug::Button("123456789123"))
		Viewer->CreateRankViewer("Player", "123456789123");
	else if (Debug::Button("123456789123456"))
		Viewer->CreateRankViewer("Player", "123456789123456");
	Debug::End();

	Viewer->Update();
}


//=============================================================================
// 描画
//=============================================================================
void UDPServer::Draw()
{
	Viewer->Draw();
}

//=============================================================================
// 受信スレッド(マルチスレッド用)
//=============================================================================
unsigned __stdcall UDPServer::ThreadEntryPoint(void* This)
{
	UDPServer* Temp = (UDPServer*)This;		// the tricky cast
	Temp->ReceivePacket();					// now call the true entry-point-function
	return 0;								// the thread exit code
}

//=============================================================================
// 受信スレッド
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

		// メッセージ受信
		recvfrom(ServerSocket, (char*)data, sizeof(data), 0, (sockaddr*)&FromAddress, &AddressLength);

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
			SplitedStr.erase(SplitedStr.begin());

			// ビューアにメッセージを設置
			// 0番 = プレイヤーの名前、1番 = AIレベル
			Viewer->CreateRankViewer(SplitedStr.at(0),SplitedStr.at(1));
		}
	}
}