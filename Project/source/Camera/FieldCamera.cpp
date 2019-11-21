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
	//startPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f)),
	//goalPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f)), 
	//TargetPos(D3DXVECTOR3(0.0f, 0.0f, 20.0f)), 
	cntFrame(0),
	currentMode(Mode::FrontSide)
{
	//const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	//target = D3DXVECTOR3(0.0f, 10.0f, 50.0f);
	//transform.SetPosition(InitPos);

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