//=====================================
//
//�r���{�[�h�I�u�W�F�N�g�w�b�_[BillboardObject.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BILLBOARDOBJECT_H_
#define _BILLBOARDOBJECT_H_

#include "../Core/GameObject.h"
#include "BillboardTransform.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BillboardObject : public GameObject
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	BillboardObject();
	BillboardObject(const BillboardObject& gameObject);
	BillboardObject(const BillboardTransform& transform);
	BillboardObject(const bool& active);
	BillboardObject(const BillboardTransform& transform, const bool& active);
	virtual ~BillboardObject() {}
};

#endif