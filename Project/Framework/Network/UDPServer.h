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

class UDPServerViewer;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServer
{
private:
	UDPServerViewer *Viewer;
	SOCKET ServerSocket;
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
