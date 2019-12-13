//=============================================================================
//
// ランキング描画クラス [RankDrawer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "RankDrawer.h"
#include "TextureDrawer.h"

#include "../../../Framework/String/String.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Math/Easing.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
const int NameDigitalMax = 3;
const int DigitalMax = 16;
const float DigitalInterval = 70.0f;
const float CharInterval = 100.0f;


//=============================================================================
// コンストラクタ
//=============================================================================
RankDrawer::RankDrawer(string Name, string AILevelStr) :
	RankNum(0),
	InScreen(true),
	AILevelStr(AILevelStr)
{
	Rank = new TextureDrawer(D3DXVECTOR2(1024.0f, 384.0f), 4, 3);
	Rank->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Ranking.png");

	PlayerName = new TextureDrawer(D3DXVECTOR2(1024.0f, 1024.0f), 6, 6);
	PlayerName->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Alphabet.png");
	PlayerName->SetSize(D3DXVECTOR2(100.0f, 100.0f));

	AILevel = new TextureDrawer(D3DXVECTOR2(512.0f, 384.0f), 4, 3);
	AILevel->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Number.png");

	SetDrawPosition();
	SplitAILevel();
	SplitName(Name);
}

//=============================================================================
// デストラクタ
//=============================================================================
RankDrawer::~RankDrawer()
{
	SAFE_DELETE(PlayerName);
	SAFE_DELETE(AILevel);
	SAFE_DELETE(Rank);
	SplitedLevel.clear();
}

//=============================================================================
// 更新
//=============================================================================
void RankDrawer::Update(void)
{
}

//=============================================================================
// 描画
//=============================================================================
void RankDrawer::Draw(void)
{
	// 画面外だったら、描画しない
	if (!InScreen)
		return;

	// 順位表示
	Rank->SetIndex(RankNum);
	Rank->Draw();

	// プレイヤーの名前表示
	for (unsigned int i = 0; i < NameDigitalMax; i++)
	{
		// 左(最大桁)から描画
		PlayerName->SetPosition(NameBasePos + D3DXVECTOR3((i * CharInterval), 0.0f, 0.0f));
		PlayerName->SetIndex(SplitedName.at(i));
		PlayerName->Draw();
	}

	// AIレベル表示
	for (unsigned int i = 0; i < SplitedLevel.size(); i++)
	{
		// 左(最大桁)から描画
		AILevel->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevel->SetIndex(SplitedLevel.at(i));
		AILevel->Draw();
	}
}

//=============================================================================
// 展開用のテクスチャを作る
//=============================================================================
void RankDrawer::CreateRankTexture(LPDIRECT3DTEXTURE9* Texture)
{
	LPDIRECT3DSURFACE9 OldSurface;
	LPDIRECT3DSURFACE9 RenderSurface;
	LPDIRECT3DTEXTURE9 RenderTexture;
	LPDIRECT3DDEVICE9 Device = GetDevice();
	const D3DXCOLOR BackColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	const D3DXVECTOR3 DrawPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 60.0f, 0.0f);
	SetPosition(DrawPos);

	//レンダーテクスチャ作成
	Device->CreateTexture(SCREEN_WIDTH, 120,
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

	// 順位表示
	Rank->SetIndex(RankNum);
	Rank->Draw();

	// プレイヤーの名前表示
	for (unsigned int i = 0; i < NameDigitalMax; i++)
	{
		// 左(最大桁)から描画
		PlayerName->SetPosition(NameBasePos + D3DXVECTOR3((i * CharInterval), 0.0f, 0.0f));
		PlayerName->SetIndex(SplitedName.at(i));
		PlayerName->Draw();
	}

	// AIレベル表示
	for (unsigned int i = 0; i < SplitedLevel.size(); i++)
	{
		// 左(最大桁)から描画
		AILevel->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevel->SetIndex(SplitedLevel.at(i));
		AILevel->Draw();
	}

	//レンダーターゲット復元
	Device->SetRenderTarget(0, OldSurface);
	SAFE_RELEASE(OldSurface);
	SAFE_RELEASE(RenderSurface);

	*Texture = RenderTexture;
	RenderTexture = nullptr;
}

//=============================================================================
// テキストとテクスチャの描画位置を設定
//=============================================================================
void RankDrawer::SetPosition(D3DXVECTOR3 Pos)
{
	CenterPos = Pos;
	InScreen = CenterPos.y > (SCREEN_HEIGHT - 60.0f) ? false : true;
	SetDrawPosition();
}

//=============================================================================
// テキストとテクスチャの描画位置を設定
//=============================================================================
void RankDrawer::SetDrawPosition(void)
{
	NameBasePos = CenterPos + D3DXVECTOR3(-250.0f, 0.0f, 0.0f);
	AILevelBasePos = CenterPos + D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	Rank->SetPosition(CenterPos + D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
}

//=============================================================================
// AILevelの文字列を分割
//=============================================================================
void RankDrawer::SplitAILevel(void)
{
	string StrTemp = AILevelStr;
	bool ZeroScore = true;

	for (int i = 0; i < DigitalMax; i++)
	{
		if (!StrTemp.empty())
		{
			// 文字列の最初1文字を取得
			char Num = StrTemp.front();

			if (Num != '0' || !ZeroScore)
			{
				ZeroScore = false;
				// int型に変換、保存
				SplitedLevel.push_back(Num - '0');
			}

			// 最初の数字削除
			StrTemp.erase(StrTemp.begin());
		}
		else
		{
			break;
		}
	}

	if (SplitedLevel.empty())
	{
		SplitedLevel.push_back(0);
	}
}

//=============================================================================
// プレイヤー名前の文字列を分割
//=============================================================================
void RankDrawer::SplitName(string NameStr)
{
	for (int i = 0; i < NameDigitalMax; i++)
	{
		if (!NameStr.empty())
		{
			// 文字列の最初2文字を取得
			string Num;
			Num.push_back(NameStr.front());
			NameStr.erase(NameStr.begin());
			Num.push_back(NameStr.front());
			NameStr.erase(NameStr.begin());

			// int型に変換、保存
			SplitedName.push_back(stoi(Num));
		}
	}
}

//=============================================================================
// AILevelの文字列をunsinged long long型に変換
//=============================================================================
unsigned long long RankDrawer::GetAILevel(void)
{
	return std::strtoull(AILevelStr.c_str(), NULL, 10);
}

//=============================================================================
// AILevelの文字列を取得
//=============================================================================
string RankDrawer::GetAILevelStr(void)
{
	return AILevelStr;
}
