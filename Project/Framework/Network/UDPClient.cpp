//=============================================================================
//
// UDP�N���C�A���g�N���X [UDPClient.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "UDPClient.h"
#include "UDPServer.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPClient::UDPClient()
{
	// WinSock������
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// �\�P�b�g����
	ClientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// �u���[�h�L���X�g����
	int value = 1;
	setsockopt(ClientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&value, sizeof(value));

	// ���M��A�h���X
	ServerAddress.sin_port = htons(ServerPort);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = inet_addr("255.255.255.255");//�u���[�h�L���X�g�A�h���X
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPClient::~UDPClient()
{
	// WinSock�I������
	closesocket(ClientSocket);
	WSACleanup();
}

//=============================================================================
// �p�P�b�g���M
//=============================================================================
void UDPClient::SendPacket()
{
	// �f�[�^���M
	string Message;
	int AddressLength;

	AddressLength = sizeof(ServerAddress);

	// ���̓��b�Z�[�W����
	Message = Packet.Header + "," + Packet.PlayerName + "," + std::to_string(Packet.AILevel);

	// ���M
	sendto(ClientSocket, Message.c_str(), Message.length() + 1, 0, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �p�P�b�g���M
//=============================================================================
void UDPClient::ReceivePacketConfig(const PacketConfig Packet)
{
	this->Packet = Packet;
}