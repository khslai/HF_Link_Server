//=============================================================================
//
// 背景クラス [Background.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "Background.h"
#include "PolygonDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../Camera/FieldCamera.h"

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
	ResourceManager::Instance()->MakePolygon("Background", "data/TEXTURE/Viewer/Background/Background.png", { 10.264f * 5, 5.773f * 5});
	//ResourceManager::Instance()->MakePolygon("Background", "data/TEXTURE/Viewer/Background/Background.png", { 57.7f, 34.2f});
	ResourceManager::Instance()->MakePolygon("Wall", "data/TEXTURE/Viewer/Background/Wall.png", { 5.0f, 5.0f });
	BG = new PolygonDrawer("Background", D3DXVECTOR3(0.0f, 10.0f, 50.0f));
	LeftWall = new PolygonDrawer("Wall", D3DXVECTOR3(-5.0f, 10.0f, 150.0f), D3DXVECTOR3(-10.264f, 10.0f, -5.0f));
	RightWall = new PolygonDrawer("Wall", D3DXVECTOR3(5.0f, 10.0f, 150.0f), D3DXVECTOR3(10.264f, 10.0f, -5.0f));
	RightWall->SetRotation(D3DXVECTOR3(0.0f, 88.0f, 0.0f));
}

//=============================================================================
// デストラクタ
//=============================================================================
Background::~Background()
{
	SAFE_DELETE(BG);
	SAFE_DELETE(LeftWall);
	SAFE_DELETE(RightWall);
	SAFE_DELETE(Ground);
}

//=============================================================================
// 更新
//=============================================================================
void Background::Update(void)
{
	LeftWall->Update();
	RightWall->Update();
}

//=============================================================================
// 描画
//=============================================================================
void Background::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	//Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//BG->Draw();
	LeftWall->Draw();
	RightWall->Draw();

	//Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}