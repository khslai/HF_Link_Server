//=====================================
//
//�r���{�[�h�g�����X�t�H�[���w�b�_[BillboardTransform.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BILLBOARDTRANSFORM_H_
#define _BILLBOARDTRANSFORM_H_

#include "../Core/Transform.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BillboardTransform : public Transform
{
	using Transform::Transform;
public:
	//���[���h�ϊ��ݒ菈��
	virtual void SetWorld(const D3DXMATRIX* parent = NULL) const override;
	virtual D3DXMATRIX GetMatrix() const override;
};

#endif