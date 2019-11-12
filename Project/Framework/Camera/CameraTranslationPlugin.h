//=====================================
//
// CameraTranslationPlugin.h
// �@�\:�J�����𕽍s�ړ�������v���O�C��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CAMERAMOVEPLUGIN_H_
#define _CAMERAMOVEPLUGIN_H_

#include "../../main.h"
#include "Camera.h"
#include "../Pattern/BaseSingleton.h"

#include <functional>

/**************************************
�N���X��`
***************************************/
class Camera::TranslationPlugin : public BaseCameraPlugin, public BaseSingleton<TranslationPlugin>
{
public:
	//����������
	void Init();

	//�X�V����
	void Update();

	//�v���O�C���K�p����
	void Apply(Camera& camera);

	//�ړ��J�n����
	//���� position : �ړ���̃J���������_
	//���� duration : �ړ��ɂ�����t���[����
	void Move(const D3DXVECTOR3& position, int duration, std::function<void(void)> callback = nullptr);

	//�ړ��O�̈ʒu�֖߂�����
	//���� duration : �ړ��ɂ�����t���[����
	void Restore(int duration, std::function<void(void)> callback = nullptr);

private:
	enum State
	{
		MoveTowards,
		RestoreBase,
		Idle
	};

	int cntFrame;							//�t���[���J�E���g
	int durationMove;						//�ړ�����
	D3DXVECTOR3 targetPosition;				//�ړ���̖ڕW���W
	State state;							//���݂̃X�e�[�g
	std::function<void(void)> callback;		//�R�[���o�b�N
};

#endif