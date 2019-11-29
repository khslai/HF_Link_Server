//=============================================================================
//
// �e�N�X�`���`��N���X [TextureTest.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include"../../main.h"
#include "TextureTest.h"
#include "../../Framework/Tool/DebugWindow.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
TextureTest::TextureTest()
{
	Texture = new TextureDrawer(D3DXVECTOR2(966.0f, 208.0f), false);
	Texture->LoadTexture("data/TEXTURE/Viewer/RankingViewer/RankingTitle.png");
	Texture->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
TextureTest::~TextureTest()
{
	SAFE_DELETE(Texture);
}

//=============================================================================
// �X�V����
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
	else if (Debug::Button("Expand_ToUpDown"))
		Texture->Expand(60.0f, ExpandType::ToUpDown, EaseType::InQuart);
	else if (Debug::Button("Close_FromUpDown"))
		Texture->Close(60.0f, CloseType::FromUpDown, EaseType::InQuart);
	else if (Debug::Button("Close_FromLeftRight"))
		Texture->Close(60.0f, CloseType::FromLeftRight, EaseType::InQuart);

	Debug::End();

	Texture->Update();
}

void TextureTest::Draw()
{
	Texture->Draw();
}