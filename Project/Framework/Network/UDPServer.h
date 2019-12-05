//=============================================================================
//
// UDPサーバークラス [UDPServer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _UDPServer_H_
#define _UDPServer_H_

#include <string>
#include <vector>
#include "../../source/Viewer/BaseViewer.h"

using namespace std;

class Background;
class RankingViewer;
class EventLiveViewer;
class Transition;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPServer
{
private:
	Background *background;
	Transition *transition;
	SOCKET ServerSocket;
	int Current;									// 現在のビューア
	bool InIdle;									// 待機状態フラグ
	std::vector<BaseViewer*> ViewerContainer;
	std::vector<std::vector<string>> RankStack;		// 追加予定のランク
	std::vector<std::vector<string>> EventStack;	// 処理待ちのイベント
	std::vector<sockaddr_in> ConnectedList;

	// クライアントからのパケットを受信
	void ReceivePacket(void);
	// 最下位のスコアを送信
	void SendLastScore(void);
	// パケット処理
	void PacketProcess(void);
	void ChangeViewer(int NextViewer, int TransitionType, std::function<void(void)> Callback = nullptr);
	void RankingRecovery(void);

#if _DEBUG
	void Debug(void);
#endif

public:
	UDPServer();
	~UDPServer();
	void Update(void);
	void DrawRanking(void);
	void DrawBackground(void);
	void SetIdle(bool Flag) { this->InIdle = Flag; };

	// マルチスレッド用
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);
};

#endif
