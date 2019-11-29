//=============================================================================
//
// �e�N�X�`���`��V�[���N���X [TextureTestScene.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "TextureTestScene.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Core/SceneManager.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Input/input.h"

/**************************************
static�����o
***************************************/


/**************************************
����������
***************************************/
void TextureTestScene::Init()
{
	textureTest = new TextureTest();
}

/**************************************
�I������
***************************************/
void TextureTestScene::Uninit()
{
	SAFE_DELETE(textureTest);
}

/**************************************
�X�V����
***************************************/
void TextureTestScene::Update()
{
	textureTest->Update();
}

/**************************************
�`�揈��
***************************************/
void TextureTestScene::Draw()
{
	textureTest->Draw();
}

