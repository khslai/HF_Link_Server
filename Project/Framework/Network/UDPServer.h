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
#include "../Pattern/BaseState.h"

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
public:
	UDPServer();
	~UDPServer();
	void Update(void);
	void DrawRanking(void);
	void DrawBackground(void);
	void ChangeViewer(int NextViewer, int TransitionType);
	void SetIdle(bool Flag) { this->InIdle = Flag; };
	void RankingRecovery(void);
	void ClearEventStack(void) { EventStack.clear(); };

	// マルチスレッド用	
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);

private:
	Background *background;
	Transition *transition;
	SOCKET ServerSocket;
	int Current;
	bool InIdle = true;
	std::vector<BaseViewer*> ViewerContainer;
	std::vector<std::vector<string>> RankStack;		// 追加予定のランク
	std::vector<std::vector<string>> EventStack;	// 追加予定のランク
	std::vector<sockaddr_in> ConnectedList;

	void ReceivePacket(void);
	void SendLastScore(void);
	void PacketProcess(void);
};

#endif
