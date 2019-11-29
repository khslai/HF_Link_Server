//=============================================================================
//
// テクスチャ描画クラス [TextureTestScene.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TextureTestScene_H_
#define _TextureTestScene_H_

#include "../../Framework/Core/BaseScene.h"
#include "../Viewer/TextureTest.h"

/**************************************
前方宣言
***************************************/


/**************************************
クラス定義
***************************************/
class TextureTestScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:

	TextureTest *textureTest;

};
#endif