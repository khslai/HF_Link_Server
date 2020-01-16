//=============================================================================
//
// ランキングビューアクラス [RankingViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
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

// ランキングの最大表示数
const int RankingMaxNum = 7;
const float RankInterval = 120.0f;
// デフォルト表示座標
const D3DXVECTOR3 DefaultPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 240.0f, 0.0f);

enum ViewerState
{
	Idle,
	Move,
	Expand,
	Recovery,
};

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
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

	// ダミーデータ
	Ranking.push_back(new RankDrawer("191018", "17849999"));
	Ranking.push_back(new RankDrawer("190113", "5739999"));
	Ranking.push_back(new RankDrawer("100813", "359999"));
	Ranking.push_back(new RankDrawer("120014", "548"));
}

//=============================================================================
// デストラクタ
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
// 更新
//=============================================================================
void RankingViewer::Update(void)
{
	const int MoveFrame = 30;
	const int RecoveryFrame = 120;
	const float MoveSpeed = RankInterval / MoveFrame;

	if (State == ViewerState::Idle)
	{
		// 追加待ちのオブジェクトがない
		if (InsertStack.empty())
		{
			CountFrame++;

			// 順番によって、表示座標を設定
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
				// ランキングビューアは待機状態
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
		ExpandTexture->Update();
	}
	else if (State == ViewerState::Recovery)
	{
		if (CountFrame < RecoveryFrame)
		{
			CountFrame++;
			int Num = 0;

			// ランキング移動
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

			// 移動終了
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
// 描画
//=============================================================================
void RankingViewer::Draw(void)
{
	// タイトル
	RankingTitle->Draw();

	// 展開演出用のテクスチャ
	if (State == ViewerState::Expand)
	{
		ExpandTexture->Draw();
	}

	// ランキング
	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}
}

//=============================================================================
// パケットの内容を処理
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
// ランキングのテクスチャを作成
//=============================================================================
void RankingViewer::CreateViewerTex(LPDIRECT3DTEXTURE9* TexturePtr)
{
	LPDIRECT3DSURFACE9 OldSurface;
	LPDIRECT3DSURFACE9 RenderSurface;
	LPDIRECT3DTEXTURE9 RenderTexture;
	LPDIRECT3DDEVICE9 Device = GetDevice();
	const D3DXCOLOR BackColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//レンダーテクスチャ作成
	Device->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&RenderTexture,
		0);

	RenderTexture->GetSurfaceLevel(0, &RenderSurface);

	//レンダーターゲット切り替え
	Device->GetRenderTarget(0, &OldSurface);
	Device->SetRenderTarget(0, RenderSurface);
	Device->Clear(0, NULL, D3DCLEAR_TARGET, BackColor, 1.0f, 0);

	// タイトル
	RankingTitle->Draw();

	// ランキング
	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}

	//レンダーターゲット復元
	Device->SetRenderTarget(0, OldSurface);
	SAFE_RELEASE(OldSurface);
	SAFE_RELEASE(RenderSurface);

	*TexturePtr = RenderTexture;
	RenderTexture = nullptr;
}

//=============================================================================
// ランキング復帰
//=============================================================================
void RankingViewer::RankingRecovery(void)
{
	int Num = 0;

	// 先に画面外に設置
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
// 最下位のスコアを取得
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
// ランキングの順番を決める
//=============================================================================
void RankingViewer::SortRanking(RankDrawer* Rank)
{
	int Num = 0;

	// 空いたら追加
	if (Ranking.empty())
	{
		InsertNum = 0;
		RankingExpand();
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
		}
		else
		{
			// 空欄がない、比較しなければならない
			for (auto &RankVec : Ranking)
			{
				unsigned long long AILevelVec = RankVec->GetAILevel();

				// スコアの比較
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
// ランキングの移動開始
//=============================================================================
void RankingViewer::RankingMoveStart(int Num)
{
	State = ViewerState::Move;
	InsertNum = Num;
	CountFrame = 0;
}

//=============================================================================
// ランキングの展開開始
//=============================================================================
void RankingViewer::RankingExpand()
{
	LPDIRECT3DTEXTURE9 NewTexture = nullptr;

	CountFrame = 0;
	State = ViewerState::Expand;

	// 順位の設定
	InsertTemp->SetRankNum(InsertNum);
	// レンダターゲットを変わる、テクスチャを生成
	InsertTemp->CreateRankTexture(&NewTexture);

	// 演出用テクスチャの設定
	ExpandTexture->LoadTexture(&NewTexture);
	ExpandTexture->SetPosition(DefaultPos + D3DXVECTOR3(300.0f, InsertNum * RankInterval, 0.0f));
	ExpandTexture->Expand(60.0f, ExpandType::LeftToRight, EaseType::InQuart, [&]()
	{
		// ランキングに追加
		RankingInsert();
	});

	// エフェクト
	GameParticleManager::Instance()->SetExpandEffect(
		DefaultPos + D3DXVECTOR3(300.0f - SCREEN_CENTER_X, InsertNum * RankInterval, 0.0f));

}

//=============================================================================
// ランキング追加処理
//=============================================================================
void RankingViewer::RankingInsert(void)
{
	InsertTemp->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, InsertNum * RankInterval, 0.0f));
	Ranking.insert(Ranking.begin() + InsertNum, InsertTemp);
	InsertTemp = nullptr;

	// 最大表示数より多ければ、最下位の人を削除
	if (Ranking.size() > RankingMaxNum)
	{
		Ranking.pop_back();
	}

	// 待機状態に戻る
	State = ViewerState::Idle;
	CountFrame = 0;
}

//=============================================================================
// アニメーションを設置する
//=============================================================================
void RankingViewer::SetAnimation(int state)
{
	if (state == ViewerState::Idle)
	{
		// ランダムでアニメーションを選択
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

		// 切り替わる間隔を再計算
		ChangeAnimInterval = Math::RandomRange(600, 900);
		CountFrame = 0;
	}
	else
	{
		// ランダムでアニメーションを選択
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