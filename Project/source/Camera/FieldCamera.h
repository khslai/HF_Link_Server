//=====================================
//
//FieldCamera.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _FIELDCAMERA_H_
#define _FIELDCAMERA_H_

#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Pattern/BaseState.h"
#include <vector>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class FieldCamera : public Camera
{
public:
	//�J�������[�h��\���񋓎q
	enum Mode
	{
		FrontSide,				//�N�H�[�^�[�r���[���[�h
		Max
	};

	//�R���X�g���N�^�A�f�X�g���N�^
	FieldCamera();
	~FieldCamera();

	//�X�V����
	void Update();

	//���[�h�ؑ֏���
	void ChangeMode(Mode next);

	//�Ǐ]�ڕW�ݒ菈��
	//void SetFollowTarget(GameObject* object);

	//�Ǐ]�ڕW���W�ݒ菈��
	void SetTargetPos(D3DXVECTOR3 TargetPos);

private:
	//GameObject *targetObject;						//�Ǐ]�ڕW
	D3DXVECTOR3 TargetPos;							//�Ǐ]�ڕW�̍��W
	D3DXVECTOR3 startPosition, goalPosition;		//�C�[�W���O�p���W
	D3DXVECTOR3 startTarget;						//�C�[�W���O�p�����_

	int cntFrame;									//�t���[���J�E���g

	Mode currentMode;								//���݂̃��[�h
	std::vector<BaseState<FieldCamera, Mode>*> fsm;	//�X�e�[�g�}�V��
	
	//�X�e�[�g�N���X
	class FieldCameraFront;
};

#endif