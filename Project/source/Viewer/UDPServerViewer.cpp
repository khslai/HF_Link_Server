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
#include "../../Framework/Math/Easing.h"

const int RankingMaxNum = 10;
const float RankInterval = 120.0f;
const D3DXVECTOR3 DefaultPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 250.0f, 0.0f);

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
UDPServerViewer::UDPServerViewer()
{
	RankingTitle = new TextureDrawer(D3DXVECTOR2(966.0f, 208.0f));
	RankingTitle->LoadTexture("data/TEXTURE/Viewer/RankingViewer/RankingTitle.png");
	RankingTitle->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 108.0f, 0.0f));
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(RankingTitle);
	Utility::DeleteContainer(Ranking);
}

//=============================================================================
// 更新
//=============================================================================
void UDPServerViewer::Update(void)
{
	if (!InMove)
	{
		// 順番によって、表示座標を設定
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
				// ランキングに追加
				Ranking.insert(Ranking.begin() + InsertNum, Temp);

				// 最大表示数より多ければ、最下位の人を削除
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
// 描画
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
// 受信スレッド(マルチスレッド用)
//=============================================================================
void UDPServerViewer::CreateRankViewer(string PlayerName, string AILevel)
{
	RankViewer* Rank = new RankViewer(PlayerName, AILevel);
	SortRanking(Rank);
}

//=============================================================================
// ランキングの順番を決める
//=============================================================================
void UDPServerViewer::SortRanking(RankViewer* Rank)
{
	int Num = 0;

	// 空いたら追加
	if (Ranking.empty())
	{
		Ranking.push_back(Rank);
	}
	else
	{
		unsigned long long AILevel = Rank->GetAILevel();

		// 最下位のスコアより少ない、かつランキングまだ空欄ある
		if (AILevel <= Ranking.back()->GetAILevel() && Ranking.size() < RankingMaxNum)
		{
			// ランキングに追加
			Ranking.push_back(Rank);
		}
		else
		{
			for (auto &RankVec : Ranking)
			{
				unsigned long long AILevelVec = RankVec->GetAILevel();

				// スコアの比較
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
// ランキングの順番を決める
//=============================================================================
void UDPServerViewer::InsertRanking(int Num, RankViewer* Rank)
{
	InMove = true;
	InsertNum = Num;
	CountFrame = 0;
	Temp = Rank;
	//// ランキングに追加
	//Ranking.insert(Ranking.begin() + Num, Rank);

	//// 最大表示数より多ければ、最下位の人を削除
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