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
#include "../Task/TaskManager.h"
#include "../Input/input.h"
#include "../../source/Viewer/RankingViewer.h"
#include "../../source/Viewer/EventLiveViewer.h"
#include "../../source/Viewer/Background.h"
#include "../../source/Viewer/Transition.h"
#include "../../source/Viewer/ViewerConfig.h"
#include "../../source/Effect/GameParticleManager.h"
#include "../../source/EventConfig.h"



//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
HANDLE UDPServer::Thread;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServer::UDPServer() :
	Current(Viewer::State::Ranking)
{
	background = new Background();
	transition = new Transition();

	ViewerContainer.resize(Viewer::State::Max);
	ViewerContainer[Viewer::State::Ranking] = new RankingViewer();
	ViewerContainer[Viewer::State::EventLive] = new EventLiveViewer();

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

	Debug::Begin("ReceivePacket");
	std::vector<string> Packet;
	Packet.resize(Packet::Max);
	Packet.at(Packet::Header) = "�����Link��p�̒ʐM�p�P�b�g�ł�";
	if (Debug::Button("RankInsert"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::InsertRank);
		Packet.at(Packet::PlayerName) = "Player";
		Packet.at(Packet::AILevel) = "123456654321";
	}
	else if (Debug::Button("NewCity"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::NewCity;
	}
	else if (Debug::Button("Meteor"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::CityDestroy;
	}
	else if (Debug::Button("AIStrike"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::BanStockUse;
	}
	else if (Debug::Button("UFO"))
	{
		Packet.at(Packet::Type) = std::to_string(Packet::EventLive);
		Packet.at(Packet::EventNo) = EventConfig::AILevelDecrease;
	}

	if (!Packet.at(Packet::Type).empty())
		PacketStack.push_back(Packet);

	Debug::End();

	Debug::Begin("ViewerChange");
	if (Debug::Button("EventViewer"))
	{
		// �G�t�F�N�g
		GameParticleManager::Instance()->SetGlassShards();
		TaskManager::Instance()->CreateDelayedTask(60, [&]()
		{
			ChangeViewer(Viewer::State::EventLive, 0);
		});
	}
	else if (Debug::Button("RankingViewer"))
	{
		ChangeViewer(Viewer::State::Ranking, 0);
		//background->RecoveryBGColor();
		//Current = Viewer::State::Ranking;
	}
	Debug::End();

#endif

	// �p�P�b�g������
	PacketProcess();

	background->Update();

	transition->Update();

	ViewerContainer.at(Current)->Update();
}


//=============================================================================
// �����L���O�`��
//=============================================================================
void UDPServer::DrawRanking()
{
	if (!transition->InActive())
	{
		ViewerContainer.at(Current)->Draw();
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
			PacketStack.push_back(SplitedStr);
		}
	}
}

//=============================================================================
// �p�P�b�g�̂���������
//=============================================================================
void UDPServer::PacketProcess(void)
{
	// �����҂��̃p�P�b�g�������
	if (!PacketStack.empty() && !InInsertRank)
	{
		// ��Ƀ����L���O�ǉ��̎���������
		for (auto &Str : PacketStack)
		{
			int Type = stoi(Str.at(Packet::Type));
			if (Type == Packet::InsertRank)
			{
				InInsertRank = true;
				ViewerContainer.at(Viewer::Ranking)->ReceivePacket(Type, Str);
			}
			Str.clear();
		}

		// ��ɑ��̎���������
		if (!InInsertRank)
		{
			for (auto &Str : PacketStack)
			{
				if (Str.empty())
					continue;

				int Type = stoi(Str.at(Packet::Type));
				if (Type == Packet::EventLive)
				{
					ViewerContainer.at(Viewer::EventLive)->ReceivePacket(Type, Str);
				}
				else if (Type == Packet::LevelUp)
				{
					//ViewerContainer.at(Viewer::)->ReceivePacket(Type, Str);
				}
				Str.clear();
			}
		}
	}

	// �󂫃p�P�b�g���폜
	PacketStack.erase(std::remove_if(std::begin(PacketStack), std::end(PacketStack), [](vector<string> Packet)
	{
		return Packet.empty();
	}), std::end(PacketStack));
}

//=============================================================================
// �r���[�A��ς���
//=============================================================================
void UDPServer::ChangeViewer(int NextViewer, int TransitionType)
{
	LPDIRECT3DTEXTURE9 ViewerTexture = nullptr;

	ViewerContainer.at(Viewer::State::Ranking)->CreateViewerTex(&ViewerTexture);
	transition->SetTransition(TransitionType, ViewerTexture);
	background->SetBGTransition(NextViewer);
	Current = NextViewer;
}
