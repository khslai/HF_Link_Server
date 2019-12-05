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
#include "../../source/Viewer/LevelUpViewer.h"
#include "../../source/Viewer/Background.h"
#include "../../source/Transition/Transition.h"
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
	Current(Viewer::State::Ranking),
	InIdle(true)
{
	background = new Background();
	transition = new Transition();

	ViewerContainer.resize(Viewer::State::Max);
	ViewerContainer[Viewer::State::Ranking] = new RankingViewer([&](bool Flag) {SetIdle(Flag); });
	ViewerContainer[Viewer::State::EventLive] = new EventLiveViewer([&]() {RankingRecovery(); });
	ViewerContainer[Viewer::State::LevelUp] = new LevelUpViewer([&]() {RankingRecovery(); });

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
	// "::"���Ȃ���bind�̃I�[�o�[���[�h��std::bind���Ăяo�����
	::bind(ServerSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
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
	RankStack.clear();
	EventStack.clear();

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
	Debug();
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
		if (SplitedStr.at(Packet::Header) == "�����Link��p�̒ʐM�p�P�b�g�ł�")
		{
			int Type = stoi(SplitedStr.at(Packet::Type));

			if (Type == Packet::InsertRank)
			{
				// �X�^�b�N�ɕ\���\��̃����N��ǉ�
				RankStack.push_back(SplitedStr);
			}
			else if (Type == Packet::EventLive || Type == Packet::LevelUp)
			{
				if (InIdle && Current == Viewer::Ranking)
				{
					// �X�^�b�N�ɕ\���\��̃C�x���g��ǉ�
					EventStack.push_back(SplitedStr);
				}
			}
			else if (Type == Packet::GetLastScore)
			{
				string Score = ((RankingViewer*)ViewerContainer.at(Viewer::Ranking))->GetLastScore();

				sendto(ServerSocket, Score.c_str(), Score.length() + 1, 0, (sockaddr*)&FromAddress, sizeof(FromAddress));
			}
		}
	}
}

//=============================================================================
// �N���C�A���g�ɍŉ��ʂ̃X�R�A�𑗂�
//=============================================================================
void UDPServer::SendLastScore(void)
{
	string Score = ((RankingViewer*)ViewerContainer.at(Viewer::Ranking))->GetLastScore();
}

//=============================================================================
// �p�P�b�g�̂���������
//=============================================================================
void UDPServer::PacketProcess(void)
{
	// �ҋ@��Ԃł����
	if (InIdle && Current == Viewer::Ranking)
	{
		// �����҂��̃p�P�b�g�������
		if (!RankStack.empty())
		{
			// ��Ƀ����L���O�ǉ��̎���������
			for (auto &Str : RankStack)
			{
				int Type = stoi(Str.at(Packet::Type));
				if (Type == Packet::InsertRank)
				{
					InIdle = false;
					ViewerContainer.at(Viewer::Ranking)->ReceivePacket(Type, Str);
				}
				Str.clear();
			}
			RankStack.clear();
		}
		// �C�x���g�p�P�b�g����
		else
		{
			if (!EventStack.empty())
			{
				for (auto &Str : EventStack)
				{
					int Type = stoi(Str.at(Packet::Type));

					// �C�x���g���p
					if (Type == Packet::EventLive)
					{
						GameParticleManager::Instance()->SetGlassShards();
						TaskManager::Instance()->CreateDelayedTask(60, [=]()
						{
							ChangeViewer(Viewer::EventLive, 0, [=]()
							{
								ViewerContainer.at(Viewer::EventLive)->ReceivePacket(Type, Str);
							});
						});
						Str.clear();
						EventStack.clear();
						break;
					}
					// �t�B�[���h���x���A�b�v
					else if (Type == Packet::LevelUp)
					{
						GameParticleManager::Instance()->SetGlassShards();
						TaskManager::Instance()->CreateDelayedTask(60, [=]()
						{
							ChangeViewer(Viewer::LevelUp, 0, [=]()
							{
								ViewerContainer.at(Viewer::LevelUp)->ReceivePacket(Type, Str);
							});
						});
						Str.clear();
						EventStack.clear();
						break;
					}
				}
			}
		}
	}
}

//=============================================================================
// �r���[�A��ς���
//=============================================================================
void UDPServer::ChangeViewer(int NextViewer, int TransitionType, std::function<void(void)> Callback)
{
	LPDIRECT3DTEXTURE9 ViewerTexture = nullptr;

	((RankingViewer*)ViewerContainer.at(Viewer::State::Ranking))->CreateViewerTex(&ViewerTexture);
	transition->SetTransition(TransitionType, ViewerTexture);
	background->SetBGTransition(NextViewer);

	TaskManager::Instance()->CreateDelayedTask(60, [=]()
	{
		Current = NextViewer;
		if (Callback != nullptr)
			Callback();
	});
}

//=============================================================================
// �����L���O�̕��A
//=============================================================================
void UDPServer::RankingRecovery(void)
{
	background->SetBGTransition(Viewer::State::Ranking);

	TaskManager::Instance()->CreateDelayedTask(60, [=]()
	{
		Current = Viewer::State::Ranking;
		((RankingViewer*)ViewerContainer.at(Viewer::State::Ranking))->RankingRecovery();
	});
}

#if _DEBUG
void UDPServer::Debug(void)
{
	Debug::Begin("UDP Server's Clients");
	for (auto &Client : ConnectedList)
	{
		Debug::Text("IP Address:%s", inet_ntoa(Client.sin_addr));
		Debug::Text("Port:%d", Client.sin_port);
		Debug::NewLine();
	}
	Debug::End();

	Debug::Begin("EventPacket");
	std::vector<string> EventPacketTemp;
	EventPacketTemp.resize(Packet::Max);
	EventPacketTemp.at(Packet::Header) = "�����Link��p�̒ʐM�p�P�b�g�ł�";
	if (Debug::Button("NewCity_City"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::NewCity);
		EventPacketTemp.at(Packet::FieldLevel) = std::to_string(FieldLevel::City);
	}
	else if (Debug::Button("NewCity_World"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::NewCity);
		EventPacketTemp.at(Packet::FieldLevel) = std::to_string(FieldLevel::World);
	}
	else if (Debug::Button("NewCity_Space"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::NewCity);
		EventPacketTemp.at(Packet::FieldLevel) = std::to_string(FieldLevel::Space);
	}
	else if (Debug::Button("Meteor"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::CityDestroy);
	}
	else if (Debug::Button("AIStrike"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::BanStockUse);
	}
	else if (Debug::Button("UFO"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::EventLive);
		EventPacketTemp.at(Packet::EventNo) = std::to_string(EventConfig::AILevelDecrease);
	}
	else if (Debug::Button("LevelUp"))
	{
		EventPacketTemp.at(Packet::Type) = std::to_string(Packet::LevelUp);
	}

	if (!EventPacketTemp.at(Packet::Type).empty())
		EventStack.push_back(EventPacketTemp);
	Debug::End();

	Debug::Begin("RankPacket");
	std::vector<string> RankPacketTemp;
	RankPacketTemp.resize(Packet::Max);
	RankPacketTemp.at(Packet::Header) = "�����Link��p�̒ʐM�p�P�b�g�ł�";
	RankPacketTemp.at(Packet::Type) = std::to_string(Packet::InsertRank);
	if (Debug::Button("123"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "123";
	}
	else if (Debug::Button("000000"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "000000";
	}
	else if (Debug::Button("001230"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "001230";
	}
	else if (Debug::Button("456789"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "456789";
	}
	else if (Debug::Button("123456789101"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "123456789101";
	}
	else if (Debug::Button("999999999999"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "999999999999";
	}
	else if (Debug::Button("2131874613284489"))
	{
		RankPacketTemp.at(Packet::PlayerName) = "000102";
		RankPacketTemp.at(Packet::AILevel) = "2131874613284489";
	}

	if (!RankPacketTemp.at(Packet::PlayerName).empty())
		RankStack.push_back(RankPacketTemp);
	Debug::End();
}
#endif