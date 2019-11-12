//=====================================
//
//PolygonResource.cpp
//�@�\:�|���S�����\�[�X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PolygonResource.h"
#include "../Renderer3D/BoardPolygon.h"

/**************************************
�R���X�g���N�^
***************************************/
PolygonResource::PolygonResource(const D3DXVECTOR2 & size, const D3DXVECTOR2 & uv, const char* path) :
	vtxBuff(nullptr),
	texture(nullptr),
	cntRef(0)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_MATERIAL) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_MATERIAL,
		D3DPOOL_MANAGED,
		&vtxBuff,
		0);

	//���_�o�b�t�@������
	VERTEX_MATERIAL *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(-size.x, size.y, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(size.x, size.y, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(size.x, -size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / uv.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f / uv.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f / uv.x, 1.0f / uv.y);

	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	vtxBuff->Unlock();

	//�e�N�X�`���ǂݍ���
	if (path != nullptr)
	{
		D3DXCreateTextureFromFile(pDevice, path, &texture);
	}
}

/**************************************
�f�X�g���N�^
***************************************/
PolygonResource::~PolygonResource()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);

	//�N���[������BoardPolygon������ɊJ������Ă��邩�m�F
	assert(cntRef == 0);
}

/**************************************
�N���[��
***************************************/
void PolygonResource::Clone(BoardPolygon * entity)
{
	if (entity == nullptr)
		return;

	entity->vtxBuff = vtxBuff;
	vtxBuff->AddRef();

	entity->texture = texture;
	texture->AddRef();

	entity->resource = this;
	cntRef++;
}

/**************************************
�����[�X���̏���
***************************************/
void PolygonResource::OnRelease()
{
	cntRef--;
}
