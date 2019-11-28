//=============================================================================
//
// トランジションクラス [Transition.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "Transition.h"
#include "Framework/TextureDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../Camera/FieldCamera.h"

#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Math/TMath.h"
#include "../../Framework/Resource/ResourceManager.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
Transition::Transition() :
	ScreenObject(SCREEN_WIDTH, SCREEN_HEIGHT),
	effect(nullptr),
	Texture(nullptr),
	Active(false),
	CountFrame(0)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	//エフェクト読み込み
	ResourceManager::Instance()->GetEffect("data/EFFECT/FlashEffect.cfx", effect);

	// ハンドル取得
	hFlashColor = effect->GetParameterByName(0, "FlashColor");
	effect->SetFloatArray(hFlashColor, (float*)&D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
}

//=============================================================================
// デストラクタ
//=============================================================================
Transition::~Transition()
{
	SAFE_RELEASE(effect);
	SAFE_RELEASE(Texture);
}

//=============================================================================
// 更新
//=============================================================================
void Transition::Update(void)
{
	if (!Active)
		return;

	CountFrame++;
	float T = (float)CountFrame / 60;
	Color = Easing::EaseValue(T, Vector3::Zero, Vector3::One, EaseType::InQuart);

	if (CountFrame >= 60)
	{
		Active = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void Transition::Draw(void)
{
	if (!Active)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetTexture(0, Texture);

	effect->Begin(0, 0);
	effect->BeginPass(0);

	effect->SetFloatArray(hFlashColor, (float*)&Color, 3);
	effect->CommitChanges();
	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

//=============================================================================
// テクスチャ読み込む
//=============================================================================
void Transition::LoadTexture(const LPDIRECT3DTEXTURE9 & Texture)
{
	if (this->Texture != nullptr)
	{
		SAFE_RELEASE(this->Texture);
	}
	this->Texture = Texture;
}

//=============================================================================
// トランジション設置
//=============================================================================
void Transition::SetTransition(int Type, const LPDIRECT3DTEXTURE9& Texture)
{
	if (this->Texture != nullptr)
	{
		SAFE_RELEASE(this->Texture);
	}
	this->Texture = Texture;

	CountFrame = 0;
	// 加算するカラー
	Color = Vector3::Zero;
	Active = true;
}
