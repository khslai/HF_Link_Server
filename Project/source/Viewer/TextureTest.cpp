//=============================================================================
//
// テクスチャ描画クラス [TextureTest.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include"../../main.h"
#include "TextureTest.h"
#include "../../Framework/Tool/DebugWindow.h"


//=============================================================================
// コンストラクタ
//=============================================================================
TextureTest::TextureTest()
{
	Texture = new TextureDrawer(D3DXVECTOR2(512.0f, 384.0f), 4, 3, false);
	Texture->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Number.png");
	Texture->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
	Texture->SetIndex(2);
}

//=============================================================================
// デストラクタ
//=============================================================================
TextureTest::~TextureTest()
{
	SAFE_DELETE(Texture);
}

//=============================================================================
// 更新処理
//=============================================================================
void TextureTest::Update()
{
	Debug::Begin("Texture Test");
	static float DestPosX = 960.0f;
	static float DestPosY = 540.0f;
	static float DestScale = 1.0f;
	static float Alpha = 1.0f;
	Debug::Input("DestPosX", DestPosX);
	Debug::Input("DestPosY", DestPosY);
	Debug::Input("DestScale", DestScale);
	Debug::Slider("Alpha", Alpha, 0.0f, 1.0f);

	if (Debug::Button("Move"))
		Texture->Move(60.0f, D3DXVECTOR3(DestPosX, DestPosY, 0.0f), EaseType::InOutCubic);
	else if (Debug::Button("Scale"))
		Texture->SetScale(60.0f, DestScale, EaseType::InOutCubic);
	else if (Debug::Button("Fade"))
		Texture->Fade(60.0f, Alpha);
	else if (Debug::Button("Expand_LeftToRight"))
		Texture->Expand(60.0f, ExpandType::LeftToRight, EaseType::InQuart);
	else if (Debug::Button("Expand_RightToLeft"))
		Texture->Expand(60.0f, ExpandType::RightToLeft, EaseType::InQuart);
	else if (Debug::Button("Expand_UpToDown"))
		Texture->Expand(60.0f, ExpandType::ExpandUpToDown, EaseType::InQuart);
	else if (Debug::Button("Expand_DownToUp"))
		Texture->Expand(60.0f, ExpandType::ExpandDownToUp, EaseType::InQuart);
	else if (Debug::Button("Expand_ToUpDown"))
		Texture->Expand(60.0f, ExpandType::ToUpDown, EaseType::InQuart);
	else if (Debug::Button("Expand_ToLeftRight"))
		Texture->Expand(60.0f, ExpandType::ToLeftRight, EaseType::InQuart);
	else if (Debug::Button("Close_FromUpDown"))
		Texture->Close(60.0f, CloseType::FromUpDown, EaseType::InQuart);
	else if (Debug::Button("Close_FromLeftRight"))
		Texture->Close(60.0f, CloseType::FromLeftRight, EaseType::InQuart);
	else if (Debug::Button("Close_UpToDown"))
		Texture->Close(60.0f, CloseType::CloseUpToDown, EaseType::InQuart);
	else if (Debug::Button("Close_DownToUp"))
		Texture->Close(60.0f, CloseType::CloseDownToUp, EaseType::InQuart);

	Debug::End();

	Texture->Update();
}

void TextureTest::Draw()
{
	Texture->Draw();
}
