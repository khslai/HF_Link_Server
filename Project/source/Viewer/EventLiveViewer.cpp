//=============================================================================
//
// �C�x���g���p�N���X [EventLiveViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "EventLiveViewer.h"
#include "Framework/TextureDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../EventConfig.h"
#include "../Viewer/ViewerConfig.h"
#include "../Booth/BoothController.h"

#include "../../Framework/Network/PacketConfig.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Task/TaskManager.h"

enum ViewerState
{
	TelopExpand,
	MessageDebut,
	MessageStop,
	MessageExit,
	TelopClose,
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
EventLiveViewer::EventLiveViewer(std::function<void()> recovery)
{
	TelopBG = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 256.0f), 1, 2, false);
	TelopBG->LoadTexture("data/TEXTURE/Viewer/EventLiveViewer/BG.png");
	TelopBG->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));

	EventMessage = new TextureDrawer(D3DXVECTOR2(1024.0f, 768.0f), 1, 6);
	EventMessage->LoadTexture("data/TEXTURE/Viewer/EventLiveViewer/Text.png");
	EventMessage->SetPosition(D3DXVECTOR3(-512.0f, SCREEN_CENTER_Y, 0.0f));

	Recovery = recovery;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
EventLiveViewer::~EventLiveViewer()
{
	SAFE_DELETE(TelopBG);
	SAFE_DELETE(EventMessage);
}

//=============================================================================
// �X�V
//=============================================================================
void EventLiveViewer::Update(void)
{
	if (State == TelopExpand)
	{
		if (!ActionFlag)
		{
			TelopBG->Expand(60.0f, ExpandType::ToUpDown, EaseType::InQuart, [&]()
			{
				SetState(ViewerState::MessageDebut);
				SetActionFlag(false);
			});
			ActionFlag = true;
		}
		else
		{
			TelopBG->Update();
		}
	}
	else if (State == MessageDebut)
	{
		if (!ActionFlag)
		{
			EventMessage->Move(120.0f, D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), EaseType::OutQuart, [&]()
			{
				RobotActor::ChangeAnim(AnimID);
				SetState(ViewerState::MessageStop);
				SetActionFlag(false);
			});
			ActionFlag = true;
		}
		else
		{
			EventMessage->Update();
		}
	}
	else if (State == MessageStop)
	{
		TaskManager::Instance()->CreateDelayedTask(15, [&]()
		{
			SetState(ViewerState::MessageExit);
			SetActionFlag(false);
		});
	}
	else if (State == MessageExit)
	{
		if (!ActionFlag)
		{
			EventMessage->Move(120.0f, D3DXVECTOR3(SCREEN_WIDTH + 512.0f, SCREEN_CENTER_Y, 0.0f), EaseType::InQuart, [&]()
			{
				SetState(ViewerState::TelopClose);
				SetActionFlag(false);
			});
			ActionFlag = true;
		}
		else
		{
			EventMessage->Update();
		}
	}
	else if (State == TelopClose)
	{
		if (!ActionFlag)
		{
			TelopBG->Close(60.0f, CloseType::FromUpDown, EaseType::OutQuart, [&]()
			{
				Recovery();
			});
			ActionFlag = true;
		}
		else
		{
			TelopBG->Update();
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void EventLiveViewer::Draw(void)
{
	TelopBG->Draw();
	EventMessage->Draw();
}

//=============================================================================
// �p�P�b�g�̓��e������
//=============================================================================
void EventLiveViewer::ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr)
{
	if (PacketType != Packet::EventLive)
		return;

	TelopBGIndex = 0;
	MessageIndex = 0;
	int EventNo = std::stoi(SpliteStr.at(Packet::EventNo));

	if (EventNo == EventConfig::NewCity)
	{
		// LED�e�[�v�𐧌�
		BoothController::Instance()->BlinkLED(BlinkType::PlusEventLED);

		int FieldLevel = std::stoi(SpliteStr.at(Packet::FieldLevel));
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

		int Rnd = Math::RandomRange(0, 2);
		if (Rnd == 0)
			AnimID = RobotActor::ShakeFist;
		else if (Rnd == 1)
			AnimID = RobotActor::Surprised;
	}
	else if (EventNo == EventConfig::CityDestroy)
	{
		// LED�e�[�v�𐧌�
		BoothController::Instance()->BlinkLED(BlinkType::MinusEventLED);

		TelopBGIndex = MinusEvent;
		MessageIndex = Meteor;
		AnimID = RobotActor::Rush;
	}
	else if (EventNo == EventConfig::AILevelDecrease)
	{
		// LED�e�[�v�𐧌�
		BoothController::Instance()->BlinkLED(BlinkType::MinusEventLED);

		TelopBGIndex = MinusEvent;
		MessageIndex = UFO;
		AnimID = RobotActor::TalkingTypeB;
	}
	else if (EventNo == EventConfig::BanStockUse)
	{
		// LED�e�[�v�𐧌�
		BoothController::Instance()->BlinkLED(BlinkType::MinusEventLED);

		TelopBGIndex = MinusEvent;
		MessageIndex = AIStrike;
		AnimID = RobotActor::Pain;
	}

	TelopBG->SetIndex(TelopBGIndex);
	EventMessage->SetIndex(MessageIndex);
	EventMessage->SetPosition(D3DXVECTOR3(-512.0f, SCREEN_CENTER_Y, 0.0f));
	State = ViewerState::TelopExpand;
	ActionFlag = false;
}
