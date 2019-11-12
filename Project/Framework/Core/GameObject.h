//=====================================
//
//�Q�[���I�u�W�F�N�g�w�b�_[GameObject.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Transform.h"
#include <memory>

class Transform;
/**************************************
�}�N����`
***************************************/

/**************************************
�Q�[���I�u�W�F�N�g���N���X
***************************************/
class GameObject
{
	friend class Tween;
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	GameObject();
	GameObject(const GameObject& gameObject);
	GameObject(const Transform& transform);
	GameObject(const bool& active);
	GameObject(const Transform& transform, const bool& active);
	GameObject(Transform* transform);
	GameObject(Transform* tranfsorm, const bool& active);
	virtual ~GameObject();

	//������Z�q
	virtual GameObject& operator=(const GameObject&);

	//�A�N�e�B�u����
	virtual bool IsActive() const;

	//�A�N�e�B�u��ԃZ�b�g����
	virtual void SetActive(bool active);

	//SRT���Q�b�^�[�i�Ȃ�ׂ��g�������Ȃ��j
	virtual D3DXVECTOR3 GetPosition() const;
	virtual D3DXVECTOR3 GetRotation() const;
	virtual D3DXVECTOR3 GetScale() const;
	virtual Transform GetTransform() const;

	//SRT���Z�b�^�[�i�Ȃ�ׂ��g�������Ȃ��j
	virtual void SetPosition(const D3DXVECTOR3& position);
	virtual void SetRotatition(const D3DXVECTOR3& rotation);
	virtual void SetScale(const D3DXVECTOR3& scale);
	virtual void SetTransform(const Transform& transform);

protected:
	//�A�N�e�B�u���
	bool active;

	//SRT���
	std::shared_ptr<Transform> transform;
};

#endif