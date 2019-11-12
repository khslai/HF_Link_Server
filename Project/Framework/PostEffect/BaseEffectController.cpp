//=====================================
//
//�e���v���[�g����[BaseEffectController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BaseEffectController.h"
#include "ScreenObject.h"

/**************************************
�R���X�g���N�^
***************************************/
BaseEffectController::BaseEffectController()
{
	renderer = new ScreenObject(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************
�f�X�g���N�^
***************************************/
BaseEffectController::~BaseEffectController()
{
	SAFE_DELETE(renderer);
}
