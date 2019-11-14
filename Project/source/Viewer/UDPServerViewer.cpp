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

const int RankingMaxNum = 10;
const float RankInterval = 120.0f;
const D3DXVECTOR3 DefaultPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, (SCREEN_HEIGHT / 10 * 2.0f + 120.0f), 0.0f);

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServerViewer::UDPServerViewer()
{
	TitleText = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 80);
	TitleText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	TitleText->SetPos((int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 10 * 2.0f));
	TitleText->SetText("�����L���O�\��");
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(TitleText);
	Utility::DeleteContainer(Ranking);
}

//=============================================================================
// �X�V
//=============================================================================
void UDPServerViewer::Update(void)
{
}

//=============================================================================
// �`��
//=============================================================================
void UDPServerViewer::Draw(void)
{
	TitleText->Draw();

	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}
}

//=============================================================================
// ��M�X���b�h(�}���`�X���b�h�p)
//=============================================================================
void UDPServerViewer::CreateRankViewer(std::vector<string> SplitedStr)
{
	// 0�� = �v���C���[�̖��O�A1�� = AI���x��
	RankViewer* Rank = new RankViewer(SplitedStr.at(0), SplitedStr.at(1));
	SortRanking(Rank);
}

//=============================================================================
// �����L���O�̏��Ԃ����߂�
//=============================================================================
void UDPServerViewer::SortRanking(RankViewer* Rank)
{
	int Num = 0;

	if (Ranking.empty())
	{
		Ranking.push_back(Rank);
	}
	else
	{
		unsigned long long AILevel = Rank->GetAILevel();
		for (auto &RankVec : Ranking)
		{
			unsigned long long AILevelVec = RankVec->GetAILevel();
			if (AILevel > AILevelVec)
			{
				Ranking.insert(Ranking.begin() + Num, Rank);
				if (Ranking.size() > RankingMaxNum)
				{
					Ranking.pop_back();
				}
				break;
			}
			else if (AILevel == AILevelVec)
			{
				Ranking.insert(Ranking.begin() + (Num + 1), Rank);
				if (Ranking.size() > RankingMaxNum)
				{
					Ranking.pop_back();
				}
				break;
			}

			Num++;
		}
	}

	Num = 0;
	for (auto &RankVec : Ranking)
	{
		RankVec->SetRankNum(Num);
		RankVec->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, Num * RankInterval, 0.0f));
		Num++;
	}
}

void UDPServerViewer::ClearRanking(void)
{
	Utility::DeleteContainer(Ranking);
}