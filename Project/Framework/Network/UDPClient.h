//=============================================================================
//
// UDP�N���C�A���g�N���X [UDPClient.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _UDPClient_H_
#define _UDPClient_H_


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPClient
{
private:
	SOCKET ClientSocket;
	sockaddr_in ServerAddress;

public:
	UDPClient();
	~UDPClient();
	void SendPacket();
};

#endif
