//=============================================================================
//
// UDPサーバー描画クラス [UDPServerViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
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
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
UDPServerViewer::UDPServerViewer()
{
	TitleText = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 80);
	TitleText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	TitleText->SetPos((int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 10 * 2.0f));
	TitleText->SetText("ランキング表示");
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(TitleText);
	Utility::DeleteContainer(Ranking);
}

//=============================================================================
// 更新
//=============================================================================
void UDPServerViewer::Update(void)
{
}

//=============================================================================
// 描画
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
// 受信スレッド(マルチスレッド用)
//=============================================================================
void UDPServerViewer::CreateRankViewer(std::vector<string> SplitedStr)
{
	// 0番 = プレイヤーの名前、1番 = AIレベル
	RankViewer* Rank = new RankViewer(SplitedStr.at(0), SplitedStr.at(1));
	SortRanking(Rank);
}

//=============================================================================
// ランキングの順番を決める
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