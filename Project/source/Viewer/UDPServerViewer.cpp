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
#include "../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"

const int RankingMaxNum = 10;
const float RankInterval = 120.0f;
const D3DXVECTOR3 DefaultPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 250.0f, 0.0f);

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
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(RankingTitle);
	Utility::DeleteContainer(Ranking);
}

//=============================================================================
// �X�V
//=============================================================================
void UDPServerViewer::Update(void)
{
	if (!InMove)
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
	else
	{
		if (CountFrame < 60)
		{
			CountFrame++;

			//float Time = CountFrame / 90.0f;
			//MoveDestPosY = Easing::EaseValue(Time, 0.0f, 120.0f, Linear);

			//for (auto Viewer = Ranking.at(InsertNum); Viewer != Ranking.end(); Viewer++)
			for (unsigned int i = InsertNum; i < Ranking.size(); i++)
			{
				D3DXVECTOR3 CenterPos = Ranking.at(i)->GetPosition();
				Ranking.at(i)->SetPosition(CenterPos + D3DXVECTOR3(0.0f, 2.0f, 0.0f));
			}

			if (CountFrame == 60)
			{
				// �����L���O�ɒǉ�
				Ranking.insert(Ranking.begin() + InsertNum, Temp);

				// �ő�\������葽����΁A�ŉ��ʂ̐l���폜
				if (Ranking.size() > RankingMaxNum)
				{
					Ranking.pop_back();
				}

				InMove = false;
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
	RankViewer* Rank = new RankViewer(PlayerName, AILevel);
	SortRanking(Rank);
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
		Ranking.push_back(Rank);
	}
	else
	{
		unsigned long long AILevel = Rank->GetAILevel();

		// �ŉ��ʂ̃X�R�A��菭�Ȃ��A�������L���O�܂��󗓂���
		if (AILevel <= Ranking.back()->GetAILevel() && Ranking.size() < RankingMaxNum)
		{
			// �����L���O�ɒǉ�
			Ranking.push_back(Rank);
		}
		else
		{
			for (auto &RankVec : Ranking)
			{
				unsigned long long AILevelVec = RankVec->GetAILevel();

				// �X�R�A�̔�r
				if (AILevel > AILevelVec)
				{
					InsertRanking(Num, Rank);
					break;
				}
				else if (AILevel == AILevelVec)
				{
					InsertRanking(Num + 1, Rank);
					break;
				}
				Num++;
			}
		}
	}
}

//=============================================================================
// �����L���O�̏��Ԃ����߂�
//=============================================================================
void UDPServerViewer::InsertRanking(int Num, RankViewer* Rank)
{
	InMove = true;
	InsertNum = Num;
	CountFrame = 0;
	Temp = Rank;
	//// �����L���O�ɒǉ�
	//Ranking.insert(Ranking.begin() + Num, Rank);

	//// �ő�\������葽����΁A�ŉ��ʂ̐l���폜
	//if (Ranking.size() > RankingMaxNum)
	//{
	//	Ranking.pop_back();
	//}
}

#if _DEBUG
void UDPServerViewer::ClearRanking(void)
{
	Utility::DeleteContainer(Ranking);
}
#endif