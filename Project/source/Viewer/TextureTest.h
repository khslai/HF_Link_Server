//=============================================================================
//
// �e�N�X�`���`��N���X [TextureTest.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _TextureTest_H_
#define _TextureTest_H_

#include "Framework/TextureDrawer.h"

//*****************************************************************************
// �N���X��`
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