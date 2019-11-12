//=====================================
//
//�r���{�[�h�I�u�W�F�N�g����[BillboardObject.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BillboardObject.h"
#include "BillboardTransform.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BillboardObject::BillboardObject() :
	GameObject(new BillboardTransform)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BillboardObject::BillboardObject(const BillboardObject &gameObject) :
	GameObject(gameObject)
{
}

/**************************************
�R���X�g���N�^
***************************************/
BillboardObject::BillboardObject(const BillboardTransform& transform) :
	GameObject(transform)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BillboardObject::BillboardObject(const bool & active) :
	GameObject(new BillboardTransform, active)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BillboardObject::BillboardObject(const BillboardTransform& transform, const bool & active) :
	GameObject(transform, active)
{

}
