//=============================================================================
//
// テクスチャ描画クラス [TextureTest.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TextureTest_H_
#define _TextureTest_H_

#include "Framework/TextureDrawer.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class TextureTest
{
private:
	TextureDrawer *Texture;

	
public:
	TextureTest();
	~TextureTest();

	void Update();
	void Draw();
};

#endif