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
const int WallNum = 2;
const int GroundNum = 8;

//=============================================================================
// コンストラクタ
//=============================================================================
Background::Background()
{
	ResourceManager::Instance()->MakePolygon("Background", "data/TEXTURE/Viewer/Background/Background.png", { 10.264f * 10, 5.773f * 10 });
	ResourceManager::Instance()->MakePolygon("Wall", "data/TEXTURE/Viewer/Background/Wall.png", { 8.0f, 4.5f });
	ResourceManager::Instance()->MakePolygon("Ground", "data/TEXTURE/Viewer/Background/Ground.png", { 10.0f, 10.0f });

	BG = new PolygonDrawer("Background", D3DXVECTOR3(0.0f, 10.0f, 100.0f));

	for (int i = 0; i < WallNum; i++)
	{
		LeftWall.push_back(new PolygonDrawer("Wall", D3DXVECTOR3(0.0f, 10.0f, 150.0f), D3DXVECTOR3(-10.264f, 10.0f, -5.0f), i));
		RightWall.push_back(new PolygonDrawer("Wall", D3DXVECTOR3(0.0f, 10.0f, 150.0f), D3DXVECTOR3(10.264f, 10.0f, -5.0f), i));
	}

	for (int i = 0; i < GroundNum; i++)
	{
		Ground.push_back(new PolygonDrawer("Ground", D3DXVECTOR3(0.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, -10.0f), i));
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
Background::~Background()
{
	SAFE_DELETE(BG);
	Utility::DeleteContainer(LeftWall);
	Utility::DeleteContainer(RightWall);
	Utility::DeleteContainer(Ground);
}

//=============================================================================
// 更新
//=============================================================================
void Background::Update(void)
{
	for (auto &Polygon : LeftWall)
	{
		Polygon->Update();
	}

	for (auto &Polygon : RightWall)
	{
		Polygon->Update();
	}

	for (auto &Polygon : Ground)
	{
		Polygon->Update();
	}
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
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	BG->Draw();
	for (auto &Polygon : LeftWall)
	{
		Polygon->Draw();
	}

	for (auto &Polygon : RightWall)
	{
		Polygon->Draw();
	}

	for (auto &Polygon : Ground)
	{
		Polygon->Draw();
	}

	//Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}