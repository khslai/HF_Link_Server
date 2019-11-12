//=====================================
//
//���V�[������[BaseScene.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BaseScene.h"

/*************************************
�R���X�g���N�^
***************************************/
BaseScene::BaseScene(LPDIRECT3DTEXTURE9 renderTexture, LPDIRECT3DSURFACE9 renderSurface) :
	renderTexture(renderTexture),
	renderSurface(renderSurface)
{
	renderTexture->AddRef();
	renderSurface->AddRef();
}

/*************************************
�f�X�g���N�^
***************************************/
BaseScene::~BaseScene()
{
	SAFE_RELEASE(renderTexture);
	SAFE_RELEASE(renderSurface);
}
