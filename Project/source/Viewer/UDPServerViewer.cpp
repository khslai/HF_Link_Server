//=============================================================================
//
// UDP�T�[�o�[�`��N���X [UDPServerViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "UDPServerViewer.h"
#include "RankViewer.h"
#include "TextureDrawer.h"
#include "../Effect/GameParticleManager.h"

#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"

const int RankingMaxNum = 10;
const float RankInterval = 120.0f;
const D3DXVECTOR3 DefaultPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 250.0f, 0.0f);

enum ViewerState
{
	Idle,
	Move,
	Expand,
	Insert,
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServerViewer::UDPServerViewer()
{
	RankingTitle = new TextureDrawer(D3DXVECTOR2(966.0f, 208.0f));
	RankingTitle->LoadTexture("data/TEXTURE/Viewer/RankingViewer/RankingTitle.png");
	RankingTitle->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 108.0f, 0.0f));

	ExpandTexture = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 120.0f));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(RankingTitle);
	SAFE_DELETE(ExpandTexture);
	InsertTemp = nullptr;
	Utility::DeleteContainer(Ranking);
}

//=============================================================================
// �X�V
//=============================================================================
void UDPServerViewer::Update(void)
{
	const int MoveFrame = 30;
	const int ExpandFrame = 60;
	const float MoveSpeed = RankInterval / MoveFrame;

	if (State == ViewerState::Idle)
	{
		// ���Ԃɂ���āA�\�����W��ݒ�
		int Num = 0;
		for (auto &RankVec : Ranking)
		{
			RankVec->SetRankNum(Num);
			RankVec->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, Num * RankInterval, 0.0f));
			Num++;
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
		if (CountFrame < ExpandFrame)
		{
			CountFrame++;
			float Time = (float)CountFrame / ExpandFrame;

			ExpandTexture->SetTextureExpand(Time);

			if (CountFrame == ExpandFrame)
			{
				RankingInsert();
				State = ViewerState::Idle;
			}
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void UDPServerViewer::Draw(void)
{
	RankingTitle->Draw();

	if (State == ViewerState::Expand)
	{
		ExpandTexture->Draw();
	}

	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}
}

//=============================================================================
// ��M�X���b�h(�}���`�X���b�h�p)
//=============================================================================
void UDPServerViewer::CreateRankViewer(string PlayerName, string AILevel)
{
	InsertTemp = new RankViewer(PlayerName, AILevel);
	SortRanking(InsertTemp);
}

//=============================================================================
// �����L���O�̏��Ԃ����߂�
//=============================================================================
void UDPServerViewer::SortRanking(RankViewer* Rank)
{
	int Num = 0;

	// �󂢂���ǉ�
	if (Ranking.empty())
	{
		InsertNum = 0;
		RankingExpand();
		//Ranking.push_back(Rank);
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
			//Ranking.push_back(Rank);
		}
		else
		{
			for (auto &RankVec : Ranking)
			{
				unsigned long long AILevelVec = RankVec->GetAILevel();

				// �X�R�A�̔�rx
				if (AILevel > AILevelVec)
				{
					RankingMoveStart(Num);
					break;
				}
				else if (AILevel == AILevelVec)
				{
					RankingMoveStart(Num + 1);
					break;
				}
				Num++;
			}
		}
	}
}

//=============================================================================
// �����L���O�̈ړ��J�n
//=============================================================================
void UDPServerViewer::RankingMoveStart(int Num)
{
	State = ViewerState::Move;
	InsertNum = Num;
	//InsertTemp = InsertRank;
	CountFrame = 0;
}

//=============================================================================
// �����L���O�̓W�J�J�n
//=============================================================================
void UDPServerViewer::RankingExpand()
{
	LPDIRECT3DTEXTURE9 NewTexture = nullptr;

	// ���ʂ̐ݒ�
	InsertTemp->SetRankNum(InsertNum);
	// �����_�^�[�Q�b�g��ς��A�e�N�X�`���𐶐�
	InsertTemp->CreateRankTexture(&NewTexture);

	// ���o�p�e�N�X�`���̐ݒ�
	ExpandTexture->LoadTexture(&NewTexture);
	ExpandTexture->SetPosition(DefaultPos + D3DXVECTOR3(300.0f, InsertNum * RankInterval, 0.0f));
	ExpandTexture->SetTextureExpand(0.0f);

	// �G�t�F�N�g
	GameParticleManager::Instance()->SetExpandEffect(
		DefaultPos + D3DXVECTOR3(300.0f - SCREEN_CENTER_X, InsertNum * RankInterval, 0.0f));

	CountFrame = 0;
	State = ViewerState::Expand;
}

//=============================================================================
// �����L���O�ǉ�����
//=============================================================================
void UDPServerViewer::RankingInsert(void)
{
	InsertTemp->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, RankInterval * InsertNum, 0.0f));
	Ranking.insert(Ranking.begin() + InsertNum, InsertTemp);
	InsertTemp = nullptr;

	// �ő�\������葽����΁A�ŉ��ʂ̐l���폜
	if (Ranking.size() > RankingMaxNum)
	{
		Ranking.pop_back();
	}
}

#if _DEBUG
void UDPServerViewer::ClearRanking(void)
{
	Utility::DeleteContainer(Ranking);
}
#endif