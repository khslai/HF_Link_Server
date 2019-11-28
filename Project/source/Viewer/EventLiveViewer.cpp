//=============================================================================
//
// �C�x���g���p�N���X [EventLiveViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "EventLiveViewer.h"
#include "Framework/SplitTextureDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../EventConfig.h"

#include "../../Framework/Network/PacketConfig.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"

enum ViewerState
{
	TelopExpand,
	MessageDebut,
	MessageStop,
	MessageExit,
	TelopClose,
};

enum FieldLevel
{
	City,
	World,
	Space,
};

enum TelopBGType
{
	PlusEvent,
	MinusEvent,
};

enum MessageType
{
	Singularity,
	Atlantis,
	NewPlanet,
	Meteor,
	UFO,
	AIStrike,
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
EventLiveViewer::EventLiveViewer()
{
	TelopBG = new SplitTextureDrawer(1, 2, D3DXVECTOR2(SCREEN_WIDTH, 512.0f), false);
	TelopBG->LoadTexture("data/TEXTURE/Viewer/EventLiveViewer/BG.png");
	TelopBG->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
EventLiveViewer::~EventLiveViewer()
{
	SAFE_DELETE(TelopBG);
	SAFE_DELETE(EventMessage);
}

void EventLiveViewer::Start(void)
{

}

//=============================================================================
// �X�V
//=============================================================================
bool EventLiveViewer::Update(void)
{
	if (!InActive)
		return true;

	if (!InIdle)
	{
		CountFrame++;
		float Time = (float)CountFrame / 60;

		if (State == TelopExpand)
		{
			TelopBG->Expand_ToUpDown(Time, EaseType::InQuart);
		}
		else if (State == MessageDebut)
		{

		}
		else if (State == MessageStop)
		{

		}
		else if (State == MessageExit)
		{

		}
		else if (State == TelopClose)
		{

		}

		if (Time >= 1.0f)
		{
			State++;
			CountFrame = 0;

			if (State > TelopClose)
			{
				InIdle = true;
			}
		}
	}

	return InIdle;
}

//=============================================================================
// �`��
//=============================================================================
void EventLiveViewer::Draw(void)
{
	TelopBG->Draw();
	//EventMessage->Draw();
}

void EventLiveViewer::Exit(void)
{

}

//=============================================================================
// �p�P�b�g�̓��e������
//=============================================================================
void EventLiveViewer::ReceivePacket(int PacketType, const std::vector<string>& SpliteStr)
{
	if (PacketType != Packet::InsertRank)
		return;

	TelopBGIndex = 0;
	MessageIndex = 0;
	int EventNo = std::stoi(SpliteStr.at(Packet::EventNo));
	int FieldLevel = std::stoi(SpliteStr.at(Packet::FieldLevel));

	if (EventNo == EventConfig::NewCity)
	{
		TelopBGIndex = PlusEvent;
		if (FieldLevel == FieldLevel::City)
		{
			MessageIndex = MessageType::Singularity;
		}
		else if (FieldLevel == FieldLevel::World)
		{
			MessageIndex = MessageType::Atlantis;
		}
		else if (FieldLevel == FieldLevel::Space)
		{
			MessageIndex = MessageType::NewPlanet;
		}
	}
	else if (EventNo == EventConfig::CityDestroy)
	{
		TelopBGIndex = MinusEvent;
		MessageIndex = Meteor;
	}
	else if (EventNo == EventConfig::AILevelDecrease)
	{
		TelopBGIndex = MinusEvent;
		MessageIndex = UFO;
	}
	else if (EventNo == EventConfig::BanStockUse)
	{
		TelopBGIndex = MinusEvent;
		MessageIndex = AIStrike;
	}
}
