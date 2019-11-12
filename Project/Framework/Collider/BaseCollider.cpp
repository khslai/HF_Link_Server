//=====================================
//
//�R���C�_�[�I�u�U�[�o�[����[ColliderObserver.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ColliderObserver.h"
#include "BaseCollider.h"

#include <algorithm>

/**************************************
�R���X�g���N�^
***************************************/
BaseCollider::BaseCollider(const std::shared_ptr<Transform> transform) :
	active(true)
{
	refTransform = transform;
}

/**************************************
�f�X�g���N�^
***************************************/
BaseCollider::~BaseCollider()
{
	refTransform.reset();
}

/**************************************
�A�N�e�B�u�Z�b�g����
***************************************/
void BaseCollider::SetActive(bool state)
{
	active = state;
}

/**************************************
�A�N�e�B�u����
***************************************/
bool BaseCollider::IsActive()
{
	return active;
}

/**************************************
�I�u�U�[�o�[�ǉ�����
***************************************/
void BaseCollider::AddObserver(ColliderObserver * observer)
{
	//�d���m�F
	auto itr = std::find(observers.begin(), observers.end(), observer);

	if (itr != observers.end())
		return;

	observers.push_back(observer);
}

/**************************************
�I�u�U�[�o�[�폜����
***************************************/
void BaseCollider::RemoveObserver(ColliderObserver * observer)
{
	//�o�^�m�F
	auto itr = std::find(observers.begin(), observers.end(), observer);

	if (itr == observers.end())
		return;

	auto newEnd = std::remove(observers.begin(), observers.end(), observer);
	observers.erase(newEnd, observers.end());
}
