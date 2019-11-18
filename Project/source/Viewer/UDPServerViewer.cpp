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
#include "RankingMask.h"
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

	RenderTexture = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 120.0f));
	//Mask = new RankingMask(D3DXVECTOR3(SCREEN_CENTER_X, 108.0f, 0.0f));
	//Mask->Set();
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(RankingTitle);
	SAFE_DELETE(RenderTexture);
	//SAFE_DELETE(Mask);
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

			if (CountFrame == MoveFrame)
			{
				// 順位の調整
				for (unsigned int i = InsertNum; i < Ranking.size(); i++)
				{
					Ranking.at(i)->SetRankNum(i + 1);
				}

				LPDIRECT3DTEXTURE9 NewTexture = nullptr;
				InsertTemp->SetRankNum(InsertNum);
				InsertTemp->CreateRankTexture(&NewTexture);
				RenderTexture->LoadTexture(&NewTexture);
				RenderTexture->SetPosition(DefaultPos + D3DXVECTOR3(300.0f, InsertNum * RankInterval, 0.0f));
				RenderTexture->SetTextureExpand(0.0f);

				State = ViewerState::Expand;
				CountFrame = 0;
			}
		}
	}
	else if (State == ViewerState::Expand)
	{
		if (CountFrame < ExpandFrame)
		{
			CountFrame++;
			float Time = (float)CountFrame / ExpandFrame;

			RenderTexture->SetTextureExpand(Time);

			if (CountFrame == ExpandFrame)
			{
				State = ViewerState::Insert;
			}
		}
	}
	else if (State == ViewerState::Insert)
	{
		InsertTemp->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, RankInterval * InsertNum, 0.0f));
		Ranking.insert(Ranking.begin() + InsertNum, InsertTemp);
		InsertTemp = nullptr;

		// 最大表示数より多ければ、最下位の人を削除
		if (Ranking.size() > RankingMaxNum)
		{
			Ranking.pop_back();
		}
		State = ViewerState::Idle;
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
		RenderTexture->Draw();
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
					RankingMoveStart(Num, Rank);
					break;
				}
				else if (AILevel == AILevelVec)
				{
					RankingMoveStart(Num + 1, Rank);
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
void UDPServerViewer::RankingMoveStart(int Num, RankViewer* Rank)
{
	State = ViewerState::Move;
	InsertNum = Num;
	InsertTemp = Rank;
	CountFrame = 0;
}

//=============================================================================
// ランキング追加処理
//=============================================================================
void UDPServerViewer::RankingInsert(void)
{

}

#if _DEBUG
void UDPServerViewer::ClearRanking(void)
{
	Utility::DeleteContainer(Ranking);
}
#endif