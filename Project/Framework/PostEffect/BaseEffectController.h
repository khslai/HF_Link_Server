//=====================================
//
//�x�[�X�G�t�F�N�g�R���g���[���w�b�_[BaseEffectController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEEFFECTCONTROLLER_H_
#define _BASEEFFECTCONTROLLER_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class ScreenObject;

/**************************************
�N���X��`
***************************************/
class BaseEffectController
{
public:
	BaseEffectController();
	~BaseEffectController();

protected:
	ScreenObject *renderer;
};

#endif