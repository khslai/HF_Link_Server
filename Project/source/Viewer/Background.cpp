//=============================================================================
//
// 背景クラス [Background.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "Background.h"
#include "Framework/PolygonDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../Camera/FieldCamera.h"
#include "ViewerConfig.h"

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
Background::Background() :
	CountFrame(0),
	CurrentBG(Background::BGType::Rank),
	PrevBG(0),
	BGChange(false)
{
	ResourceManager::Instance()->MakePolygon("Background_Rank", "data/TEXTURE/Viewer/Background/Background_Rank.png", Viewer::BackGroundSize);
	ResourceManager::Instance()->MakePolygon("Background_Event", "data/TEXTURE/Viewer/Background/Background_Event.png", Viewer::BackGroundSize);
	ResourceManager::Instance()->MakePolygon("Background_LevelUp", "data/TEXTURE/Viewer/Background/Background_LevelUp.png", Viewer::BackGroundSize);
	ResourceManager::Instance()->MakePolygon("Wall", "data/TEXTURE/Viewer/Background/Wall.png", { 8.0f, 4.5f });
	ResourceManager::Instance()->MakePolygon("Ground", "data/TEXTURE/Viewer/Background/Ground.png", { 10.0f, 10.0f });


	background.reserve(Background::BGType::Max);
	background.push_back(new PolygonDrawer("Background_Rank", Viewer::BackgroundPos));
	background.push_back(new PolygonDrawer("Background_Event", Viewer::BackgroundPos));
	background.at(Background::BGType::Event)->SetAlpha(0.0f);
	background.push_back(new PolygonDrawer("Background_LevelUp", Viewer::BackgroundPos));
	background.at(Background::BGType::LevelUp)->SetAlpha(0.0f);

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
	Utility::DeleteContainer(background);
	Utility::DeleteContainer(LeftWall);
	Utility::DeleteContainer(RightWall);
	Utility::DeleteContainer(Ground);
}

//=============================================================================
// 更新
//=============================================================================
void Background::Update(void)
{
	if (BGChange)
	{
		CountFrame++;
		float Time = (float)CountFrame / 60;
		//D3DXCOLOR Color = Easing::EaseValue(Time, PreColor, DestColor, EaseType::Linear);
		float Alpha = Easing::EaseValue(Time, 0.0f, 1.0f, EaseType::Linear);
		background.at(PrevBG)->SetAlpha(1.0f - Alpha);
		background.at(CurrentBG)->SetAlpha(Alpha);

		if (CountFrame >= 60)
		{
			BGChange = false;
		}
	}

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
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	for (auto &Polygon : background)
	{
		Polygon->Draw();
	}

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

//=============================================================================
// 背景のトランジション
//=============================================================================
void Background::SetBGTransition(int NextBG)
{
	this->PrevBG = CurrentBG;
	this->CurrentBG = NextBG;
	CountFrame = 0;
	BGChange = true;
}

//=============================================================================
// ランキングの背景に復帰
//=============================================================================
void Background::RecoveryBGColor(void)
{
	PrevBG = CurrentBG;
	CurrentBG = Background::BGType::Rank;

	CountFrame = 0;
	BGChange = true;
}
