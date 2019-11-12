//=====================================
//
//�Q�[���I�u�W�F�N�g����[GameObject.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameObject.h"
#include "Transform.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
GameObject::GameObject() :
	transform(std::make_shared<Transform>()),
	active(true)
{

}

/**************************************
�R���X�g���N�^
***************************************/
GameObject::GameObject(const GameObject& gameObject) :
	transform(std::make_shared<Transform>(*gameObject.transform)),
	active(true)
{
	
}

/**************************************
�R���X�g���N�^
***************************************/
GameObject::GameObject(const Transform& transform) :
	transform(std::make_shared<Transform>(transform)),
	active(true)
{

}

/**************************************
�R���X�g���N�^
***************************************/
GameObject::GameObject(const bool& active) :
	transform(std::make_shared<Transform>()),
	active(active)
{

}

/**************************************
�R���X�g���N�^
***************************************/
GameObject::GameObject(const Transform& transform, const bool& active) :
	transform(std::make_shared<Transform>(transform)),
	active(active)
{

}

/**************************************
�R���X�g���N�^
***************************************/
GameObject::GameObject(Transform * transform) :
	active(true)
{
	this->transform.reset(transform);
}

/**************************************
�R���X�g���N�^
***************************************/
GameObject::GameObject(Transform* transform, const bool & active) :
	active(active)
{
	this->transform.reset(transform);
}

/**************************************
������Z�q
***************************************/
GameObject& GameObject::operator=(const GameObject& other)
{
	std::shared_ptr<Transform> sptr = transform;
	transform.reset();

	transform = std::make_shared<Transform>(*other.transform);
	return *this;
}

/**************************************
�f�X�g���N�^
***************************************/
GameObject::~GameObject()
{
	transform.reset();
}

/**************************************
�A�N�e�B�u����
***************************************/
bool GameObject::IsActive() const 
{
	return active;
}

/**************************************
�A�N�e�B�u��ԃZ�b�g����
***************************************/
void GameObject::SetActive(bool active)
{
	this->active = active;
}

/**************************************
���W�Z�b�g
***************************************/
D3DXVECTOR3 GameObject::GetPosition() const
{
	return transform->GetPosition();
}
/**************************************
���W�Q�b�g
***************************************/
void GameObject::SetPosition(const D3DXVECTOR3& position)
{
	transform->SetPosition(position);
}

/**************************************
��]�p�x�Q�b�g
***************************************/
D3DXVECTOR3 GameObject::GetRotation() const
{
	return transform->GetEulerAngle();
}

/**************************************
��]�p�x�Z�b�g
***************************************/
void GameObject::SetRotatition(const D3DXVECTOR3& rotation)
{
	transform->SetRotation(rotation);
}

/**************************************
�X�P�[���Q�b�g
***************************************/
D3DXVECTOR3 GameObject::GetScale() const
{
	return transform->GetScale();
}

/**************************************
�X�P�[���Z�b�g
***************************************/
void GameObject::SetScale(const D3DXVECTOR3& scale)
{
	transform->SetScale(scale);
}

/**************************************
SRT���Q�b�g
***************************************/
Transform GameObject::GetTransform() const
{
	return *transform;
}

/**************************************
�X�P�[�����Q�b�g
***************************************/
void GameObject::SetTransform(const Transform& transform)
{
	*this->transform = transform;
}