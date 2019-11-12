//=====================================
//
//�{�b�N�X�R���C�_�[3D�w�b�_[BoxCollider3D.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOXCOLLIDER3D_H_
#define _BOXCOLLIDER3D_H_

#define BOXCOLLIDER3D_USE_DEBUG

#include "../../main.h"
#include "BaseCollider.h"
#include "ColliderObserver.h"

/**************************************
BoxCollider3D�N���X
***************************************/
class BoxCollider3D : public BaseCollider
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	BoxCollider3D(const std::string& tag, const std::shared_ptr<Transform>& transform);
	BoxCollider3D(const std::string& tag, const std::shared_ptr<Transform>& transform, const D3DXVECTOR3& size);
	~BoxCollider3D();

	//�Փ˔���A�T�C�Y�Z�b�g�A���W�A�h���X�Z�b�g
	bool CheckCollision(BoxCollider3D& other);
	void SetSize(const D3DXVECTOR3 size);
	void SetOffset(const D3DXVECTOR3 offset);

	//ID�擾
	unsigned GetUniqueID() const;

	//�f�o�b�O�\��
	void Draw();

private:
	std::string tag;		//�^�O
	D3DXVECTOR3 size;		//�T�C�Y
	D3DXVECTOR3 offset;		//�I�t�Z�b�g
	
	unsigned uniqueID;				//���j�[�NID
	static unsigned incrementID;	//�C���N�������gID


#ifdef BOXCOLLIDER3D_USE_DEBUG
	static UINT instanceCount;		//�C���X�^���X�J�E���g
	static void CreateRenderTool();
	static D3DMATERIAL9 material;	//�`��p�}�e���A��
	static LPD3DXMESH mesh;			//�`��p���b�V��
#endif
};
#endif