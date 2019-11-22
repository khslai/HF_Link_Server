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
#include "../../source/Viewer/EventLiveViewer.h"
#include "../../source/Viewer/Background.h"


//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
HANDLE UDPServer::Thread;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServer::UDPServer()
{
	background = new Background();
	RankingViewer = new UDPServerViewer();

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
	SAFE_DELETE(background);
	SAFE_DELETE(EventViewer);
	SAFE_DELETE(RankingViewer);
	ConnectedList.clear();

	// WinSock�I������
	closesocket(ServerSocket);
	WSACleanup();

	// ===============================================================
	// ���ӁB������ƃX���b�h�I���֐�(_endthreadex)���Ă΂Ȃ���
	// ���C���X���b�h���I��������ɑ��̃X���b�h�͂��̂܂܎��s���܂�
	// ��O�X���[�̉\��������
	// ===============================================================
	// �X���b�h���������܂ő҂�
	DWORD ThreadResult = WaitForSingleObject(Thread, INFINITE);
	if (ThreadResult == WAIT_OBJECT_0)
	{
		// �X���b�h�I��
		CloseHandle(Thread);
	}
}

//=============================================================================
// �X�V
//=============================================================================
void UDPServer::Update(void)
{
#if _DEBUG
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
		RankingViewer->ClearRanking();
	else if (Debug::Button("123"))
		RankingViewer->CreateRankViewer("Player", "123");
	else if (Debug::Button("123455"))
		RankingViewer->CreateRankViewer("Player", "123455");
	else if (Debug::Button("123456"))
		RankingViewer->CreateRankViewer("Player", "123456");
	else if (Debug::Button("123457"))
		RankingViewer->CreateRankViewer("Player", "123457");
	else if (Debug::Button("123456789"))
		RankingViewer->CreateRankViewer("Player", "123456789");
	else if (Debug::Button("123456789123"))
		RankingViewer->CreateRankViewer("Player", "123456789123");
	else if (Debug::Button("123456789123456"))
		RankingViewer->CreateRankViewer("Player", "123456789123456");
	Debug::End();
#endif

	background->Update();

	if (!RankStack.empty())
	{
		for (auto &Str : RankStack)
		{
			// �����L���O�r���[�A�����
			// 0�� = �v���C���[�̖��O�A1�� = AI���x��
			RankingViewer->CreateRankViewer(Str.at(0), Str.at(1));
			Str.clear();
		}
		RankStack.clear();
	}

	RankingViewer->Update();
}


//=============================================================================
// �����L���O�`��
//=============================================================================
void UDPServer::DrawRanking()
{
	RankingViewer->Draw();
}

//=============================================================================
// �w�i�`��
//=============================================================================
void UDPServer::DrawBackground(void)
{
	background->Draw();
}

//=============================================================================
// ��M�X���b�h(�}���`�X���b�h�p)
//=============================================================================
unsigned __stdcall UDPServer::ThreadEntryPoint(void* This)
{
	UDPServer* Temp = (UDPServer*)This;
	Temp->ReceivePacket();					// �{���̃Z�J���h�X���b�h�̏����֐�
	_endthreadex(0);						// �X���b�h�̎��s��~
	return 0;								
}

//=============================================================================
// ��M�X���b�h
// �ł������A�}���`�X���b�h�̊֐��ɒ������Ԃ������鏈���������Ȃ��悤��
// �ǂ����Ă��������Ԃ��K�v�����ȏꍇ�AWaitForSingleObject�̑҂��Ԃ𒷂�����
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

		// ������̃N���A
		memset(data, 0, sizeof(data));

		// ���b�Z�[�W��M
		recvfrom(ServerSocket, (char*)data, sizeof(data), 0, (sockaddr*)&FromAddress, &AddressLength);

		// ServerSocket���������recvfrom�͔�΂����̂�
		// �������[�v����o�邽�߂̏������͕K�v
		if (strcmp(data, "") == 0)
		{
			break;
		}

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

			// �X�^�b�N�ɕ\���\��̃I�u�W�F�N�g��ǉ�
			RankStack.push_back(SplitedStr);
		}
	}
}