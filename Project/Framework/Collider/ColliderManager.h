//=====================================
//
//�R���C�_�[�}�l�[�W���w�b�_[ColliderManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _COLLIDERMANAGER_H_
#define _COLLIDERMANAGER_H_

#include "BoxCollider3D.h"
#include "../Pattern/BaseSingleton.h"

#include <unordered_map>
#include <list>
#include <string>
#include <memory>
#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class ColliderManager : public BaseSingleton<ColliderManager>
{
public:
	//�{�b�N�X�R���C�_�[�쐬����
	std::shared_ptr<BoxCollider3D> CreateBoxCollider(const std::string& tag, const std::shared_ptr<Transform> transform);
	std::shared_ptr<BoxCollider3D> CreateBoxCollider(const std::string& tag, const std::shared_ptr<Transform> transform, const D3DXVECTOR3& size);

	//�X�V����
	void Update();

	//�N���A����
	void Clear();

	//�Փ˔���
	void CheckRoundRobin(const std::string& tag1, const std::string& tag2);

private:
	//�{�b�N�X�R���C�_�[�R���e�i
	std::unordered_map <std::string, std::list<std::weak_ptr<BoxCollider3D>>> boxColliderMap;
	
};

#endif