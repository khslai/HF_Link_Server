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

using namespace std;

class Background;
class UDPServerViewer;
class EventLiveViewer;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServer
{
private:
	Background *background;
	EventLiveViewer *EventViewer;			// �C�x���g���p�r���[�A
	UDPServerViewer *RankingViewer;			// �����L���O�\���r���[�A
	SOCKET ServerSocket;
	std::vector<std::vector<string>> RankStack;		// �ǉ��\��̃����N
	std::vector<sockaddr_in> ConnectedList;

	void ReceivePacket(void);

public:
	UDPServer();
	~UDPServer();
	void Update(void);
	void Draw(void);

	// �}���`�X���b�h�p
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);
};

#endif
