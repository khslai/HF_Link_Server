//=============================================================================
//
// テクスチャ描画シーンクラス [TextureTestScene.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "TextureTestScene.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Core/SceneManager.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Input/input.h"

/**************************************
staticメンバ
***************************************/


/**************************************
初期化処理
***************************************/
void TextureTestScene::Init()
{
	textureTest = new TextureTest();
}

/**************************************
終了処理
***************************************/
void TextureTestScene::Uninit()
{
	SAFE_DELETE(textureTest);
}

/**************************************
更新処理
***************************************/
void TextureTestScene::Update()
{
	textureTest->Update();
}

/**************************************
描画処理
***************************************/
void TextureTestScene::Draw()
{
	textureTest->Draw();
}

