//=============================================================================
//
// �����L���O�r���[�A�N���X [RankingViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "RankingViewer.h"
#include "ViewerConfig.h"
#include "Framework/RankDrawer.h"
#include "Framework/TextureDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../Actor/RobotActor.h"

#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Network/PacketConfig.h"

// �����L���O�̍ő�\����
const int RankingMaxNum = 7;
const float RankInterval = 120.0f;
// �f�t�H���g�\�����W
const D3DXVECTOR3 DefaultPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 240.0f, 0.0f);

enum ViewerState
{
	Idle,
	Move,
	Expand,
	Recovery,
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
RankingViewer::RankingViewer(std::function<void(bool)> setIdle) :
	InsertTemp(nullptr),
	ChangeAnimInterval(Math::RandomRange(600, 900)),
	EventHappened(false)
{
	RankingTitle = new TextureDrawer(D3DXVECTOR2(966.0f, 208.0f));
	RankingTitle->LoadTexture("data/TEXTURE/Viewer/RankingViewer/RankingTitle.png");
	RankingTitle->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 108.0f, 0.0f));

	ExpandTexture = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 120.0f), false);

	SetIdle = setIdle;

	// �_�~�[�f�[�^
	Ranking.push_back(new RankDrawer("191018", "17849999"));
	Ranking.push_back(new RankDrawer("190113", "5739999"));
	Ranking.push_back(new RankDrawer("100813", "359999"));
	Ranking.push_back(new RankDrawer("120014", "548"));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
RankingViewer::~RankingViewer()
{
	SAFE_DELETE(RankingTitle);
	SAFE_DELETE(ExpandTexture);
	SAFE_DELETE(InsertTemp);
	Utility::DeleteContainer(Ranking);
	Utility::DeleteContainer(InsertStack);
}

//=============================================================================
// �X�V
//=============================================================================
void RankingViewer::Update(void)
{
	const int MoveFrame = 30;
	const int RecoveryFrame = 120;
	const float MoveSpeed = RankInterval / MoveFrame;

	if (State == ViewerState::Idle)
	{
		// �ǉ��҂��̃I�u�W�F�N�g���Ȃ�
		if (InsertStack.empty())
		{
			CountFrame++;

			// ���Ԃɂ���āA�\�����W��ݒ�
			int Num = 0;
			for (auto &RankVec : Ranking)
			{
				RankVec->SetRankNum(Num);
				RankVec->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, Num * RankInterval, 0.0f));
				Num++;
			}

			if (CountFrame % ChangeAnimInterval == 0)
			{
				SetAnimation(State);
			}

			if (!EventHappened)
			{
				// �����L���O�r���[�A�͑ҋ@���
				SetIdle(true);
			}
		}
		else
		{
			InsertTemp = InsertStack.at(0);
			InsertStack.erase(InsertStack.begin());
			SortRanking(InsertTemp);
		}
	}
	else if (State == ViewerState::Move)
	{
		if (CountFrame < MoveFrame)
		{
			CountFrame++;

			// ���X�ɉ��Ɉړ�����
			for (unsigned int i = InsertNum; i < Ranking.size(); i++)
			{
				D3DXVECTOR3 CenterPos = Ranking.at(i)->GetPosition();
				Ranking.at(i)->SetPosition(CenterPos + D3DXVECTOR3(0.0f, MoveSpeed, 0.0f));
			}

			// �ړ��I��
			if (CountFrame == MoveFrame)
			{
				// ���ʂ̒���
				for (unsigned int i = InsertNum; i < Ranking.size(); i++)
				{
					Ranking.at(i)->SetRankNum(i + 1);
				}

				// �����L���O�W�J
				RankingExpand();
			}
		}
	}
	else if (State == ViewerState::Expand)
	{
		ExpandTexture->Update();
	}
	else if (State == ViewerState::Recovery)
	{
		if (CountFrame < RecoveryFrame)
		{
			CountFrame++;
			int Num = 0;

			// �����L���O�ړ�
			for (auto &RankVec : Ranking)
			{
				float Time = (float)CountFrame / (RecoveryFrame - Num * 15);
				D3DXVECTOR3 StartPos = RankVec->GetStartPos();
				D3DXVECTOR3 DestPos = DefaultPos + D3DXVECTOR3(0.0f, Num * RankInterval, 0.0f);
				D3DXVECTOR3 Pos = Easing::EaseValue(Time, StartPos, DestPos, EaseType::OutQuart);
				RankVec->SetPosition(Pos);
				Num++;
			}

			RankingTitle->Update();

			// �ړ��I��
			if (CountFrame == RecoveryFrame)
			{
				State = ViewerState::Idle;
				CountFrame = 0;
				SetIdle(true);
				EventHappened = false;
			}
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void RankingViewer::Draw(void)
{
	// �^�C�g��
	RankingTitle->Draw();

	// �W�J���o�p�̃e�N�X�`��
	if (State == ViewerState::Expand)
	{
		ExpandTexture->Draw();
	}

	// �����L���O
	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}
}

//=============================================================================
// �p�P�b�g�̓��e������
//=============================================================================
void RankingViewer::ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr)
{
	if (PacketType != Packet::InsertRank)
		return;

	string Name = SpliteStr.at(Packet::PlayerName);
	string AILevel = SpliteStr.at(Packet::AILevel);

	if (InsertTemp == nullptr)
	{
		InsertTemp = new RankDrawer(Name, AILevel);
		SortRanking(InsertTemp);
	}
	else
	{
		InsertStack.push_back(new RankDrawer(Name, AILevel));
	}
}

//=============================================================================
// �����L���O�̃e�N�X�`�����쐬
//=============================================================================
void RankingViewer::CreateViewerTex(LPDIRECT3DTEXTURE9* TexturePtr)
{
	LPDIRECT3DSURFACE9 OldSurface;
	LPDIRECT3DSURFACE9 RenderSurface;
	LPDIRECT3DTEXTURE9 RenderTexture;
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

	// �^�C�g��
	RankingTitle->Draw();

	// �����L���O
	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}

	//�����_�[�^�[�Q�b�g����
	Device->SetRenderTarget(0, OldSurface);
	SAFE_RELEASE(OldSurface);
	SAFE_RELEASE(RenderSurface);

	*TexturePtr = RenderTexture;
	RenderTexture = nullptr;
}

//=============================================================================
// �����L���O���A
//=============================================================================
void RankingViewer::RankingRecovery(void)
{
	int Num = 0;

	// ��ɉ�ʊO�ɐݒu
	for (auto &RankVec : Ranking)
	{
		RankVec->SetPosition(DefaultPos + D3DXVECTOR3(-SCREEN_WIDTH, Num * RankInterval, 0.0f));
		RankVec->SetStartPos(DefaultPos + D3DXVECTOR3(-SCREEN_WIDTH, Num * RankInterval, 0.0f));
		Num++;
	}

	RankingTitle->SetAlpha(0.0f);
	RankingTitle->Fade(60.0f, 1.0f);

	State = ViewerState::Recovery;
	CountFrame = 0;
}

//=============================================================================
// �ŉ��ʂ̃X�R�A���擾
//=============================================================================
string RankingViewer::GetLastScore(void)
{
	if (Ranking.size() < RankingMaxNum)
	{
		return "0";
	}
	else
	{
		return Ranking.back()->GetAILevelStr();
	}
}

//=============================================================================
// �����L���O�̏��Ԃ����߂�
//=============================================================================
void RankingViewer::SortRanking(RankDrawer* Rank)
{
	int Num = 0;

	// �󂢂���ǉ�
	if (Ranking.empty())
	{
		InsertNum = 0;
		RankingExpand();
	}
	else
	{
		unsigned long long AILevel = Rank->GetAILevel();

		// �ŉ��ʂ̃X�R�A��菭�Ȃ��A�������L���O�܂��󗓂���
		if (AILevel <= Ranking.back()->GetAILevel() && Ranking.size() < RankingMaxNum)
		{
			// �����L���O�ɒǉ�
			InsertNum = Ranking.size();
			RankingExpand();
		}
		else
		{
			// �󗓂��Ȃ��A��r���Ȃ���΂Ȃ�Ȃ�
			for (auto &RankVec : Ranking)
			{
				unsigned long long AILevelVec = RankVec->GetAILevel();

				// �X�R�A�̔�r
				if (AILevel > AILevelVec)
				{
					RankingMoveStart(Num);
					break;
				}
				else if (AILevel == AILevelVec && Ranking.size() < RankingMaxNum)
				{
					RankingMoveStart(Num + 1);
					break;
				}
				Num++;
			}
		}
	}

	SetAnimation(State);
}

//=============================================================================
// �����L���O�̈ړ��J�n
//=============================================================================
void RankingViewer::RankingMoveStart(int Num)
{
	State = ViewerState::Move;
	InsertNum = Num;
	CountFrame = 0;
}

//=============================================================================
// �����L���O�̓W�J�J�n
//=============================================================================
void RankingViewer::RankingExpand()
{
	LPDIRECT3DTEXTURE9 NewTexture = nullptr;

	CountFrame = 0;
	State = ViewerState::Expand;

	// ���ʂ̐ݒ�
	InsertTemp->SetRankNum(InsertNum);
	// �����_�^�[�Q�b�g��ς��A�e�N�X�`���𐶐�
	InsertTemp->CreateRankTexture(&NewTexture);

	// ���o�p�e�N�X�`���̐ݒ�
	ExpandTexture->LoadTexture(&NewTexture);
	ExpandTexture->SetPosition(DefaultPos + D3DXVECTOR3(300.0f, InsertNum * RankInterval, 0.0f));
	ExpandTexture->Expand(60.0f, ExpandType::LeftToRight, EaseType::InQuart, [&]()
	{
		// �����L���O�ɒǉ�
		RankingInsert();
	});

	// �G�t�F�N�g
	GameParticleManager::Instance()->SetExpandEffect(
		DefaultPos + D3DXVECTOR3(300.0f - SCREEN_CENTER_X, InsertNum * RankInterval, 0.0f));

}

//=============================================================================
// �����L���O�ǉ�����
//=============================================================================
void RankingViewer::RankingInsert(void)
{
	InsertTemp->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, InsertNum * RankInterval, 0.0f));
	Ranking.insert(Ranking.begin() + InsertNum, InsertTemp);
	InsertTemp = nullptr;

	// �ő�\������葽����΁A�ŉ��ʂ̐l���폜
	if (Ranking.size() > RankingMaxNum)
	{
		Ranking.pop_back();
	}

	// �ҋ@��Ԃɖ߂�
	State = ViewerState::Idle;
	CountFrame = 0;
}

//=============================================================================
// �A�j���[�V������ݒu����
//=============================================================================
void RankingViewer::SetAnimation(int state)
{
	if (state == ViewerState::Idle)
	{
		// �����_���ŃA�j���[�V������I��
		int Rnd = Math::RandomRange(0, 5);
		if (Rnd == 0)
			RobotActor::ChangeAnim(RobotActor::Waving);
		else if (Rnd == 1)
			RobotActor::ChangeAnim(RobotActor::Salute);
		else if (Rnd == 2)
			RobotActor::ChangeAnim(RobotActor::WaveHand);
		else if (Rnd == 3)
			RobotActor::ChangeAnim(RobotActor::TalkingTypeA);
		else if (Rnd == 4)
			RobotActor::ChangeAnim(RobotActor::FightingIdle);

		// �؂�ւ��Ԋu���Čv�Z
		ChangeAnimInterval = Math::RandomRange(600, 900);
		CountFrame = 0;
	}
	else
	{
		// �����_���ŃA�j���[�V������I��
		int Rnd = Math::RandomRange(0, 3);
		if (Rnd == 0)
			RobotActor::ChangeAnim(RobotActor::Clapping);
		else if (Rnd == 1)
			RobotActor::ChangeAnim(RobotActor::FistPump);
		else if (Rnd == 2)
			RobotActor::ChangeAnim(RobotActor::Yeah);
	}
}

#if _DEBUG
void RankingViewer::ClearRanking(void)
{
	Utility::DeleteContainer(Ranking);
}
#endif