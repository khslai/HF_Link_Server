//=============================================================================
//
// UDP�T�[�o�[�N���X [UDPServer.h]
// Author : HAL���� GP12B332 41 ���M��
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
// �N���X��`
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

	// �}���`�X���b�h�p	
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);

private:
	Background *background;
	Transition *transition;
	SOCKET ServerSocket;
	int Current;
	bool InIdle = true;
	std::vector<BaseViewer*> ViewerContainer;
	std::vector<std::vector<string>> RankStack;		// �ǉ��\��̃����N
	std::vector<std::vector<string>> EventStack;	// �ǉ��\��̃����N
	std::vector<sockaddr_in> ConnectedList;

	void ReceivePacket(void);
	void SendLastScore(void);
	void PacketProcess(void);
};

#endif
