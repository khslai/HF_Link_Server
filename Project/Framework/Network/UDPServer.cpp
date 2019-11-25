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
#include "../../source/Viewer/Transition.h"

#include "../Input/input.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
HANDLE UDPServer::Thread;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServer::UDPServer() :
	Current(State::Ranking)
{
	background = new Background();
	//RankingViewer = new UDPServerViewer();
	transition = new Transition();

	ViewerContainer.resize(State::Max);
	ViewerContainer[State::Ranking] = new UDPServerViewer();
	ViewerContainer[State::Event] = new EventLiveViewer();

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
	SAFE_DELETE(transition);
	Utility::DeleteContainer(ViewerContainer);
	//SAFE_DELETE(EventViewer);
	//SAFE_DELETE(RankingViewer);
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

	if (Keyboard::GetTrigger(DIK_F))
	{
		CreateViewerTexture();
		transition->SetTransition();
		Current = State::Event;
	}
	if (Keyboard::GetTrigger(DIK_G))
	{
		Current = State::Ranking;
	}
	if (Keyboard::GetTrigger(DIK_D))
	{
		vector<string> Test;
		Test.push_back("�����Link��p�̒ʐM�p�P�b�g�ł�");
		Test.push_back("1");
		Test.push_back("Potato");
		Test.push_back("118486132189");
		RankStack.push_back(Test);
	}
#endif

	if (Current == State::Ranking)
	{
		if (!RankStack.empty())
		{
			for (auto &Str : RankStack)
			{
				int Type = stoi(Str.at(Packet::Rank::Type));
				ViewerContainer.at(Current)->ReceivePacket(Type, Str);
				//RankingViewer->CreateRankViewer(Str.at(0), Str.at(1));
				Str.clear();
			}
			RankStack.clear();
		}
	}

	background->Update();

	transition->Update();

	ViewerContainer.at(Current)->Update();
	//RankingViewer->Update();

}


//=============================================================================
// �����L���O�`��
//=============================================================================
void UDPServer::DrawRanking()
{
	if (!transition->InActive())
	{
		ViewerContainer.at(Current)->Draw();
		//RankingViewer->Draw();
	}
	else
	{
		transition->Draw();
	}
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
			//SplitedStr.erase(SplitedStr.begin());

			// �X�^�b�N�ɕ\���\��̃I�u�W�F�N�g��ǉ�
			RankStack.push_back(SplitedStr);
		}
	}
}

void UDPServer::CreateViewerTexture(void)
{
	LPDIRECT3DSURFACE9 OldSurface;
	LPDIRECT3DSURFACE9 RenderSurface;
	static LPDIRECT3DTEXTURE9 RenderTexture;
	LPDIRECT3DDEVICE9 Device = GetDevice();
	const D3DXCOLOR BackColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//�����_�[�e�N�X�`���쐬
	Device->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&RenderTexture,
		0);

	RenderTexture->GetSurfaceLevel(0, &RenderSurface);

	//�����_�[�^�[�Q�b�g�؂�ւ�
	Device->GetRenderTarget(0, &OldSurface);
	Device->SetRenderTarget(0, RenderSurface);
	Device->Clear(0, NULL, D3DCLEAR_TARGET, BackColor, 1.0f, 0);

	ViewerContainer.at(State::Ranking)->Draw();

	//�����_�[�^�[�Q�b�g����
	Device->SetRenderTarget(0, OldSurface);
	SAFE_RELEASE(OldSurface);
	SAFE_RELEASE(RenderSurface);

	transition->LoadTexture(RenderTexture);
	RenderTexture = nullptr;
}
