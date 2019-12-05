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
private:
	Background *background;
	Transition *transition;
	SOCKET ServerSocket;
	int Current;									// ���݂̃r���[�A
	bool InIdle;									// �ҋ@��ԃt���O
	std::vector<BaseViewer*> ViewerContainer;
	std::vector<std::vector<string>> RankStack;		// �ǉ��\��̃����N
	std::vector<std::vector<string>> EventStack;	// �����҂��̃C�x���g
	std::vector<sockaddr_in> ConnectedList;

	// �N���C�A���g����̃p�P�b�g����M
	void ReceivePacket(void);
	// �ŉ��ʂ̃X�R�A�𑗐M
	void SendLastScore(void);
	// �p�P�b�g����
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

	// �}���`�X���b�h�p
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);
};

#endif
