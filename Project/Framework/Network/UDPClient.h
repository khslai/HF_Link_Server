//=============================================================================
//
// UDP�N���C�A���g�N���X [UDPClient.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _UDPClient_H_
#define _UDPClient_H_

#include "PacketConfig.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPClient
{
private:
	SOCKET ClientSocket;
	sockaddr_in ServerAddress;
	PacketConfig Packet;

public:
	UDPClient();
	~UDPClient();
	void SendPacket();
	void ReceivePacketConfig(PacketConfig Packet);
};

#endif
