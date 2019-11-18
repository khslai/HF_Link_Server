//=============================================================================
//
// ランキングマスククラス [RankingMask.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "RankingMask.h"

#include "../../Framework/Math/Easing.h"

/**************************************
マクロ定義
***************************************/


/**************************************
コンストラクタ
***************************************/
RankingMask::RankingMask(D3DXVECTOR3 Pos)
{
	//ポリゴン初期化
	rect = new RectangleMask();
	rect->LoadTexture("data/TRANSITION/RectangleMask.png");
	rect->SetSize((float)SCREEN_WIDTH / 2, 120.0f);
	rect->SetPosition(Pos);
}

/**************************************
デストラクタ
***************************************/
RankingMask::~RankingMask()
{
	SAFE_DELETE(rect);
}

/**************************************
更新処理
***************************************/
MaskResult RankingMask::Update()
{
	if (!active)
		return Continuous;

	MaskResult result = MaskResult::Continuous;

	cntFrame++;

	rect->Update();

	//トランジションの終了確認
	//if (cntFrame == 120)
	//{
	//	// マスクをオフに
	//	active = false;

	//	result = isTransitionOut ? FinishTransitionOut : FinishTransitionIn;
	//}
	return result;
}

/**************************************
トランジション開始処理
***************************************/
void RankingMask::Draw()
{
	if (!active)
		return;

	BeginMask();

	rect->Draw();

	EndMask();
}



/**************************************
トランジション開始処理
***************************************/
void RankingMask::Set(void)
{
	//すでにマスク中であれば開始しない
	if (active)
		return;

	//イージング開始
	rect->Init();

	//フラグ初期化
	cntFrame = 0;
	active = true;
}

/**************************************
トランジション開始処理
***************************************/
void RankingMask::Set(bool isTransitionOut)
{
}

//=====================================================
// RectangleMask Class
//=====================================================
/**************************************
回転六角形初期化処理
***************************************/
void RectangleMask::Init(void)
{
	const D3DXVECTOR3 InitScale =  Vector3::One;
	const D3DXVECTOR3 EndScale = Vector3::One - InitScale;
	const EaseType Type = EaseType::InQuart;

	//Tween::Scale(*this, InitScale, EndScale, HEXATRANSITION_DURATION, Type);
}

/**************************************
回転六角形更新処理
***************************************/
void RectangleMask::Update()
{
	//transform->Rotate(0.0f, 0.0f, 10.0f);
}

