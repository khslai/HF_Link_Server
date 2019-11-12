//=====================================
//
//FIeldCamera.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldCamera.h"
#include "State/FieldCameraFront.h"
#include "../../Framework/Input/input.h"

/**************************************
�R���X�g���N�^
***************************************/
FieldCamera::FieldCamera() :
	//targetObject(NULL),
	startPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	goalPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), 
	cntFrame(0),
	currentMode(Mode::FrontSide)
{
	////�p�����[�^�ݒ�
	//const float CameraAngleXZ = D3DXToRadian(45.0f);
	//const float CameraAngleY = D3DXToRadian(60.0f);
	//const float CameraLength = 50.0f;

	//const D3DXVECTOR3 InitPos = D3DXVECTOR3(
	//	cosf(CameraAngleY) * cosf(CameraAngleXZ),
	//	sinf(CameraAngleY),
	//	cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	//�X�e�[�g�}�V���쐬
	fsm.resize(Mode::Max);
	fsm[Mode::FrontSide] = new FieldCameraFront();
}

/**************************************
�f�X�g���N�^
***************************************/
FieldCamera::~FieldCamera()
{
	Utility::DeleteContainer(fsm);
}

/**************************************
�X�V����
***************************************/
void FieldCamera::Update()
{
	//�X�e�[�g�̍X�V
	fsm[currentMode]->OnUpdate(*this);

	Camera::Update();
}

/**************************************
���[�h�ؑ֏���
***************************************/
void FieldCamera::ChangeMode(Mode next)
{
	currentMode = next;

	fsm[currentMode]->OnStart(*this);
}

///**************************************
//�Ǐ]�ڕW�ݒ菈��
//***************************************/
//void FieldCamera::SetFollowTarget(GameObject * object)
//{
//	targetObject = object;
//}

/**************************************
�Ǐ]�ڕW���W�ݒ菈��
***************************************/
void FieldCamera::SetTargetPos(D3DXVECTOR3 TargetPos)
{
	this->TargetPos = TargetPos;
}