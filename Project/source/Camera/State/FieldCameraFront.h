//=====================================
//
// �t�B�[���h�J����(����)�N���X[FieldCameraFront.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _FieldCameraFront_H_
#define _FieldCameraFront_H_

#include "../../../main.h"
#include "../FieldCamera.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera::FieldCameraFront : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);
};
#endif