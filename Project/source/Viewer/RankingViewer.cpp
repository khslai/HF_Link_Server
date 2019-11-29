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
	InsertTemp(nullptr)
{
	RankingTitle = new TextureDrawer(D3DXVECTOR2(966.0f, 208.0f));
	RankingTitle->LoadTexture("data/TEXTURE/Viewer/RankingViewer/RankingTitle.png");
	RankingTitle->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 108.0f, 0.0f));

	ExpandTexture = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 120.0f), false);

	SetIdle = setIdle;
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
bool RankingViewer::Update(void)
{
	const int MoveFrame = 30;
	const int RecoveryFrame = 120;
	const float MoveSpeed = RankInterval / MoveFrame;

	if (State == ViewerState::Idle)
	{
		// 追加待ちのオブジェクトがない
		if (InsertStack.empty())
		{
			// 順番によって、表示座標を設定
			int Num = 0;
			for (auto &RankVec : Ranking)
			{
				RankVec->SetRankNum(Num);
				RankVec->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, Num * RankInterval, 0.0f));
				Num++;
			}
			// ランキングビューアは待機状態
			SetIdle(true);
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
			}
		}
	}

#if _DEBUG
	Debug::Begin("Ranking Test");
	if (Debug::Button("Clear"))
		ClearRanking();
	else if (Debug::Button("123"))
		CreateRankDrawer("112233", "123");
	else if (Debug::Button("123455"))
		CreateRankDrawer("001234", "123455");
	else if (Debug::Button("123456"))
		CreateRankDrawer("000102", "123456");
	else if (Debug::Button("123457"))
		CreateRankDrawer("030405", "123457");
	else if (Debug::Button("123456789"))
		CreateRankDrawer("060708", "123456789");
	else if (Debug::Button("123456789123"))
		CreateRankDrawer("091011", "123456789123");
	else if (Debug::Button("123456789123456"))
		CreateRankDrawer("333435", "123456789123456");
	Debug::End();
#endif

	return InIdle;
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
void RankingViewer::CreateRankDrawer(string PlayerName, string AILevel)
{
	if (InsertTemp == nullptr)
	{
		InsertTemp = new RankDrawer(PlayerName, AILevel);
		SortRanking(InsertTemp);
	}
	else
	{
		InsertStack.push_back(new RankDrawer(PlayerName, AILevel));
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
	return Ranking.back()->GetAILevelStr();
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

	CountFrame = 0;
	State = ViewerState::Expand;
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

	State = ViewerState::Idle;
}

#if _DEBUG
void RankingViewer::ClearRanking(void)
{
	Utility::DeleteContainer(Ranking);
}
#endif