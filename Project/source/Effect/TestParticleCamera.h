//=====================================
//
// TestParticleCamera.h
// �@�\:�p�[�e�B�N���e�X�g�V�[���̃J����
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TESTPARTICLECAMERA_H_
#define _TESTPARTICLECAMERA_H_

#include "../../main.h"
#include "../../Framework/Camera/Camera.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TestParticleCamera : public Camera
{
public:
	TestParticleCamera();

	void Update() override;
};

#endif