//=============================================================================
//
// 背景クラス [Background.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "Background.h"
#include "TextureDrawer.h"
#include "../Effect/GameParticleManager.h"

#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#include "../../Framework/Resource/ResourceManager.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
Background::Background()
{
	ResourceManager::Instance()->MakePolygon("Background", "data/TEXTURE/Viewer/Background/Background.png", { 120.0f, 68.0f});
	BG = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("Background", BG);
}

//=============================================================================
// デストラクタ
//=============================================================================
Background::~Background()
{
	SAFE_DELETE(BG);
}

//=============================================================================
// 更新
//=============================================================================
void Background::Update(void)
{

}

//=============================================================================
// 描画
//=============================================================================
void Background::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// テスト描画
	Transform transform = Transform(
		D3DXVECTOR3(0.0f, 10.0f, 100.0f),
		Vector3::Zero,
		Vector3::One);

	BG->Draw(transform.GetMatrix());

	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}