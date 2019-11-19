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

	ExpandTexture = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 120.0f));
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(RankingTitle);
	SAFE_DELETE(ExpandTexture);
	InsertTemp = nullptr;
	Utility::DeleteContainer(Ranking);
}

//=============================================================================
// 更新
//=============================================================================
void UDPServerViewer::Update(void)
{
	const int MoveFrame = 30;
	const int ExpandFrame = 60;
	const float MoveSpeed = RankInterval / MoveFrame;

	if (State == ViewerState::Idle)
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
	else if (State == ViewerState::Move)
	{
		if (CountFrame < MoveFrame)
		{
			CountFrame++;

			// 徐々に下に移動する
			for (unsigned int i = InsertNum; i < Ranking.size(); i++)
			{
				D3DXVECTOR3 CenterPos = Ranking.at(i)->GetPosition();
				Ranking.at(i)->SetPosition(CenterPos + D3DXVECTOR3(0.0f, MoveSpeed, 0.0f));
			}

			// 移動終了
			if (CountFrame == MoveFrame)
			{
				// 順位の調整
				for (unsigned int i = InsertNum; i < Ranking.size(); i++)
				{
					Ranking.at(i)->SetRankNum(i + 1);
				}

				// ランキング展開
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
// 描画
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
// 受信スレッド(マルチスレッド用)
//=============================================================================
void UDPServerViewer::CreateRankViewer(string PlayerName, string AILevel)
{
	InsertTemp = new RankViewer(PlayerName, AILevel);
	SortRanking(InsertTemp);
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
		InsertNum = 0;
		RankingExpand();
		//Ranking.push_back(Rank);
	}
	else
	{
		unsigned long long AILevel = Rank->GetAILevel();

		// 最下位のスコアより少ない、かつランキングまだ空欄ある
		if (AILevel <= Ranking.back()->GetAILevel() && Ranking.size() < RankingMaxNum)
		{
			// ランキングに追加
			InsertNum = Ranking.size();
			RankingExpand();
			//Ranking.push_back(Rank);
		}
		else
		{
			for (auto &RankVec : Ranking)
			{
				unsigned long long AILevelVec = RankVec->GetAILevel();

				// スコアの比較x
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
// ランキングの移動開始
//=============================================================================
void UDPServerViewer::RankingMoveStart(int Num)
{
	State = ViewerState::Move;
	InsertNum = Num;
	//InsertTemp = InsertRank;
	CountFrame = 0;
}

//=============================================================================
// ランキングの展開開始
//=============================================================================
void UDPServerViewer::RankingExpand()
{
	LPDIRECT3DTEXTURE9 NewTexture = nullptr;

	// 順位の設定
	InsertTemp->SetRankNum(InsertNum);
	// レンダターゲットを変わる、テクスチャを生成
	InsertTemp->CreateRankTexture(&NewTexture);

	// 演出用テクスチャの設定
	ExpandTexture->LoadTexture(&NewTexture);
	ExpandTexture->SetPosition(DefaultPos + D3DXVECTOR3(300.0f, InsertNum * RankInterval, 0.0f));
	ExpandTexture->SetTextureExpand(0.0f);

	// エフェクト
	GameParticleManager::Instance()->SetExpandEffect(
		DefaultPos + D3DXVECTOR3(300.0f - SCREEN_CENTER_X, InsertNum * RankInterval, 0.0f));

	CountFrame = 0;
	State = ViewerState::Expand;
}

//=============================================================================
// ランキング追加処理
//=============================================================================
void UDPServerViewer::RankingInsert(void)
{
	InsertTemp->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, RankInterval * InsertNum, 0.0f));
	Ranking.insert(Ranking.begin() + InsertNum, InsertTemp);
	InsertTemp = nullptr;

	// 最大表示数より多ければ、最下位の人を削除
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