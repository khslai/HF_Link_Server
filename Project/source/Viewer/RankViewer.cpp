//=============================================================================
//
// ランキング描画クラス [RankViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "RankViewer.h"
#include "TextureDrawer.h"

#include "../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************
const int DigitalMax = 16;
const float DigitalInterval = 70.0f;


//=============================================================================
// コンストラクタ
//=============================================================================
RankViewer::RankViewer(string Name, string AILevelStr) :
	RankNum(0),
	InScreen(true),
	AILevelStr(AILevelStr)
{
	RankDrawer = new TextureDrawer(4, 3, D3DXVECTOR2(1024.0f, 384.0f));
	RankDrawer->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Ranking.png");

	PlayerName = new TextViewer("data/TEXTURE/Viewer/RankingViewer/Text_cinecaption226.ttf", 80);
	PlayerName->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	PlayerName->SetText(Name);

	AILevelDrawer = new TextureDrawer(4, 3, D3DXVECTOR2(512.0f, 384.0f));
	AILevelDrawer->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Number.png");

	SetDrawPosition();
	SplitAILevel();
}

//=============================================================================
// デストラクタ
//=============================================================================
RankViewer::~RankViewer()
{
	SAFE_DELETE(PlayerName);
	SAFE_DELETE(AILevelDrawer);
	SAFE_DELETE(RankDrawer);
	SplitedInt.clear();
}

//=============================================================================
// 更新
//=============================================================================
void RankViewer::Update(void)
{
}

//=============================================================================
// 描画
//=============================================================================
void RankViewer::Draw(void)
{
	// 画面外だったら、描画しない
	if (!InScreen)
		return;

	// 順位表示
	RankDrawer->SetTexture(RankNum);
	RankDrawer->Draw();

	// プレイヤーの名前表示
	PlayerName->Draw();

	// AIレベル表示
	//for (int i = 0; i < DigitalMax; i++)
	for (unsigned int i = 0; i < SplitedInt.size(); i++)
	{
		// 左(最大桁)から描画
		//AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((DigitalMax - i) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetTexture(SplitedInt.at(i));
		AILevelDrawer->Draw();
	}
}

//=============================================================================
// テキストとテクスチャの描画位置を設定
//=============================================================================
void RankViewer::SetPosition(D3DXVECTOR3 Pos)
{
	CenterPos = Pos;
	InScreen = CenterPos.y > SCREEN_HEIGHT ? false : true;
	SetDrawPosition();
}

//=============================================================================
// テキストとテクスチャの描画位置を設定
//=============================================================================
void RankViewer::SetDrawPosition(void)
{
	PlayerName->SetPos((int)(CenterPos.x - 200), (int)(CenterPos.y));
	AILevelBasePos = CenterPos + D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	RankDrawer->SetPosition(CenterPos + D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
}

//=============================================================================
// AILevelの文字列を分割
//=============================================================================
void RankViewer::SplitAILevel(void)
{
	string StrTemp = AILevelStr;

	for (int i = 0; i < DigitalMax; i++)
	{
		if (!StrTemp.empty())
		{
			// 文字列の最初1文字を取得
			char Num = StrTemp.front();

			// int型に変換、保存
			SplitedInt.push_back(Num - '0');

			// 最初の数字削除
			StrTemp.erase(StrTemp.begin());
		}
		else
		{
			break;
			//SplitedInt.push_back(0);
		}
	}
}

//=============================================================================
// AILevelの文字列をunsinged long long型に変換
//=============================================================================
unsigned long long RankViewer::GetAILevel(void)
{
	return std::strtoull(AILevelStr.c_str(), NULL, 10);
}