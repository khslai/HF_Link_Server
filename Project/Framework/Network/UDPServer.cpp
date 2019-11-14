//=============================================================================
//
// UDP�T�[�o�[�N���X [UDPServer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "UDPServer.h"
#include "PacketConfig.h"
#include "../String/String.h"
#include "../Tool/DebugWindow.h"
#include "../../source/Viewer/UDPServerViewer.h"



//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
HANDLE UDPServer::Thread;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServer::UDPServer()
{
	Viewer = new UDPServerViewer();

	// WinSock������
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// �\�P�b�g����
	ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ��M�A�h���X�ƃ|�[�g�ԍ�
	sockaddr_in ServerAddress;
	ServerAddress.sin_port = htons(ServerPort);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = INADDR_ANY;

	// �\�P�b�g�ɖ��O��t����
	bind(ServerSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPServer::~UDPServer()
{
	// ���������
	SAFE_DELETE(Viewer);
	ConnectedList.clear();

	// �X���b�h���
	CloseHandle(Thread);

	// WinSock�I������
	closesocket(ServerSocket);
	WSACleanup();
}

//=============================================================================
// �X�V
//=============================================================================
void UDPServer::Update(void)
{
	Debug::Begin("UDP Server's Clients");
	for (auto &Client : ConnectedList)
	{
		Debug::Text("IP Address:%s", inet_ntoa(Client.sin_addr));
		Debug::Text("Port:%d", Client.sin_port);
		Debug::NewLine();
	}
	Debug::End();

	Debug::Begin("Ranking Test");
	if (Debug::Button("Clear"))
		Viewer->ClearRanking();
	else if (Debug::Button("123"))
		Viewer->CreateRankViewer("Player", "123");
	else if (Debug::Button("123455"))
		Viewer->CreateRankViewer("Player", "123455");
	else if (Debug::Button("123456"))
		Viewer->CreateRankViewer("Player", "123456");
	else if (Debug::Button("123457"))
		Viewer->CreateRankViewer("Player", "123457");
	else if (Debug::Button("123456789"))
		Viewer->CreateRankViewer("Player", "123456789");
	else if (Debug::Button("123456789123"))
		Viewer->CreateRankViewer("Player", "123456789123");
	else if (Debug::Button("123456789123456"))
		Viewer->CreateRankViewer("Player", "123456789123456");
	Debug::End();

	Viewer->Update();
}


//=============================================================================
// �`��
//=============================================================================
void UDPServer::Draw()
{
	Viewer->Draw();
}

//=============================================================================
// ��M�X���b�h(�}���`�X���b�h�p)
//=============================================================================
unsigned __stdcall UDPServer::ThreadEntryPoint(void* This)
{
	UDPServer* Temp = (UDPServer*)This;		// the tricky cast
	Temp->ReceivePacket();					// now call the true entry-point-function
	return 0;								// the thread exit code
}

//=============================================================================
// ��M�X���b�h
//=============================================================================
void UDPServer::ReceivePacket(void)
{
	// �f�[�^��M
	char data[256];
	int AddressLength;
	sockaddr_in FromAddress;

	while (true)
	{
		AddressLength = sizeof(FromAddress);

		// ���b�Z�[�W��M
		recvfrom(ServerSocket, (char*)data, sizeof(data), 0, (sockaddr*)&FromAddress, &AddressLength);

#if _DEBUG
		// ���M����IP�A�h���X�����Ƀ��X�g�̒����ǂ������m�F
		bool Existed = false;
		for (auto &Address : ConnectedList)
		{
			if (Address.sin_port == FromAddress.sin_port &&
				strcmp(inet_ntoa(Address.sin_addr), inet_ntoa(FromAddress.sin_addr)) == 0)
			{
				Existed = true;
				break;
			}
		}

		// �ڑ����X�g�ɐV�����N���C�A���g��ǉ�
		if (!Existed)
		{
			ConnectedList.push_back(FromAddress);
		}
#endif

		string Message = data;
		// ��M����������𕪊�
		std::vector<string> SplitedStr;
		String::Split(SplitedStr, Message, ',');

		// �p�P�b�g�̃w�b�_�[���m�F
		if (SplitedStr.at(0) == "�����Link��p�̒ʐM�p�P�b�g�ł�")
		{
			SplitedStr.erase(SplitedStr.begin());

			// �r���[�A�Ƀ��b�Z�[�W��ݒu
			// 0�� = �v���C���[�̖��O�A1�� = AI���x��
			Viewer->CreateRankViewer(SplitedStr.at(0),SplitedStr.at(1));
		}
	}
}