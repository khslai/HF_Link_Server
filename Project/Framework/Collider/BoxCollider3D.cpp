//=====================================
//
//�{�b�N�X�R���C�_�[3D����[BoxCollider3D.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BoxCollider3D.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
static�ϐ�
***************************************/
unsigned BoxCollider3D::incrementID = 0;

#ifdef BOXCOLLIDER3D_USE_DEBUG
UINT BoxCollider3D::instanceCount;
D3DMATERIAL9 BoxCollider3D::material;
LPD3DXMESH BoxCollider3D::mesh;
#endif

/**************************************
�R���X�g���N�^
***************************************/
BoxCollider3D::BoxCollider3D(const std::string & tag, const std::shared_ptr<Transform> & transform) :
	BaseCollider(transform),
	tag(tag),
	uniqueID(incrementID++)
{
	//�T�C�Y��K���ȑ傫���ɏ�����
	const float InitSize = 10.0;
	size = D3DXVECTOR3(InitSize, InitSize, InitSize);

	//�I�t�Z�b�g��������
	ZeroMemory(&offset, sizeof(offset));


#ifdef BOXCOLLIDER3D_USE_DEBUG
	//�C���X�^���X���𐔂��ăf�o�b�O�\���p�̃��b�V�����쐬
	if (instanceCount == 0)
		CreateRenderTool();
	instanceCount++;
#endif

}

/**************************************
�R���X�g���N�^
***************************************/
BoxCollider3D::BoxCollider3D(const std::string & tag, const std::shared_ptr<Transform> & transform, const D3DXVECTOR3 & size) :
	BaseCollider(transform),
	size(size),
	tag(tag),
	uniqueID(incrementID++)
{
	//�I�t�Z�b�g��������
	ZeroMemory(&offset, sizeof(offset));

#ifdef BOXCOLLIDER3D_USE_DEBUG
	if (instanceCount == 0)
		CreateRenderTool();
	instanceCount++;
#endif
}

/**************************************
�f�X�g���N�^
***************************************/
BoxCollider3D::~BoxCollider3D()
{
	//TODO : ColliderManager�ɗ��E��ʒm

#ifdef BOXCOLLIDER3D_USE_DEBUG
	instanceCount--;
	if (instanceCount == 0)
	{
		SAFE_RELEASE(mesh);
	}
#endif
}

/**************************************
�Փ˔���
***************************************/
bool BoxCollider3D::CheckCollision(BoxCollider3D& other)
{
	D3DXVECTOR3 thisPos = this->refTransform->GetPosition() + this->offset;
	D3DXVECTOR3 otherPos = other.refTransform->GetPosition() + other.offset;
	
	D3DXVECTOR3 thisSize = Vector3::Multiply(this->size, this->refTransform->GetScale());
	D3DXVECTOR3 otherSize = Vector3::Multiply(other.size, other.refTransform->GetScale());

	//X�����̔���
	if (thisPos.x + thisSize.x < otherPos.x - otherSize.x || thisPos.x - thisSize.x > otherPos.x + otherSize.x)
		return false;

	//Y�����̔���
	if (thisPos.y + thisSize.y < otherPos.y - otherSize.y || thisPos.y - thisSize.y > otherPos.y + otherSize.y)
		return false;

	//Z�����̔���
	if (thisPos.z + thisSize.z < otherPos.z - otherSize.z || thisPos.z - thisSize.z > otherPos.z + otherSize.z)
		return false;

	//�Փ˒ʒm
	for (auto&& observer : this->observers)
	{
		observer->OnColliderHit(other.tag);
	}
	for (auto&& observer : other.observers)
	{
		observer->OnColliderHit(this->tag);
	}

	return true;
}

/**************************************
�T�C�Y�Z�b�g
***************************************/
void BoxCollider3D::SetSize(D3DXVECTOR3 size)
{
	this->size = size;
}

/**************************************
�I�t�Z�b�g�Z�b�g
***************************************/
void BoxCollider3D::SetOffset(const D3DXVECTOR3 offset)
{
	this->offset = offset;
}

/**************************************
���j�[�NID�擾
***************************************/
unsigned BoxCollider3D::GetUniqueID() const
{
	return uniqueID;
}

#ifdef BOXCOLLIDER3D_USE_DEBUG
/**************************************
�`��}�e���A���쐬����
***************************************/
void BoxCollider3D::CreateRenderTool()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�L���[�u���b�V���쐬
	D3DXCreateBox(pDevice,
		1.0f,
		1.0f,
		1.0f,
		&mesh,
		0);

	//�}�e���A���쐬
	ZeroMemory(&material, sizeof(material));
	material.Diffuse.r = 1.0f;
	material.Diffuse.a = 1.0f;
	material.Ambient.r = 1.0f;
	material.Ambient.a = 1.0f;
	material.Specular.r = 1.0f;
	material.Specular.a = 1.0f;
	material.Emissive.r = 1.0f;
	material.Emissive.a = 1.0f;
}
#endif

/**************************************
�`�揈��
***************************************/
void BoxCollider3D::Draw()
{
#ifdef BOXCOLLIDER3D_USE_DEBUG
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld;
	D3DMATERIAL9 matDef;

	//�f�t�H���g�}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�����_�[�X�e�[�g�ƃ}�e���A����ݒ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetMaterial(&material);
	pDevice->SetTexture(0, NULL);

	//�s��v�Z
	D3DXVECTOR3 pos = refTransform->GetPosition() + offset;
	D3DXVECTOR3 scale = Vector3::Multiply(refTransform->GetScale(), size) * 2.0f;

	D3DXMatrixIdentity(&mtxWorld);
	mtxWorld._11 = scale.x;
	mtxWorld._22 = scale.y;
	mtxWorld._33 = scale.z;
	mtxWorld._41 = pos.x;
	mtxWorld._42 = pos.y;
	mtxWorld._43 = pos.z;

	//���[���h���Z�b�g
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�`��
	mesh->DrawSubset(0);

	//�����_�[�X�e�[�g�ƃ}�e���A������
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pDevice->SetMaterial(&matDef);
#endif
}