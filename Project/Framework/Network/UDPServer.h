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

using namespace std;

class Background;
class UDPServerViewer;
class EventLiveViewer;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPServer
{
private:
	Background *background;
	EventLiveViewer *EventViewer;			// イベント中継ビューア
	UDPServerViewer *RankingViewer;			// ランキング表示ビューア
	SOCKET ServerSocket;
	std::vector<std::vector<string>> RankStack;		// 追加予定のランク
	std::vector<sockaddr_in> ConnectedList;

	void ReceivePacket(void);

public:
	UDPServer();
	~UDPServer();
	void Update(void);
	void Draw(void);

	// マルチスレッド用
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);
};

#endif
