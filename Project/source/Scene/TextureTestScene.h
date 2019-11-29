//=============================================================================
//
// �e�N�X�`���`��N���X [TextureTestScene.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _TextureTestScene_H_
#define _TextureTestScene_H_

#include "../../Framework/Core/BaseScene.h"
#include "../Viewer/TextureTest.h"

/**************************************
�O���錾
***************************************/


/**************************************
�N���X��`
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