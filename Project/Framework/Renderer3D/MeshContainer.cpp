//=====================================
//
//���b�V���R���e�i����[MeshContainer.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MeshContainer.h"
#include "../Resource/MeshResource.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
MeshContainer::MeshContainer() :
	mesh(NULL),
	materialNum(0),
	resource(NULL),
	initialized(false)
{

}

/**************************************
�f�X�g���N�^
***************************************/
MeshContainer::~MeshContainer()
{
	ReleaseResource();
}

/**************************************
�`�揈��
***************************************/
void MeshContainer::Draw()
{
	D3DMATERIAL9 matDef;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�}�e���A���ޔ�
	pDevice->GetMaterial(&matDef);

	for (DWORD i = 0; i < materialNum; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, textures[i]);

		//�}�e���A���ݒ�
		pDevice->SetMaterial(&materials[i]);

		//�`��
		mesh->DrawSubset(i);
	}

	//�}�e���A������
	pDevice->SetMaterial(&matDef);
}

/**************************************
���f���̃��C���[�t���[����`��
***************************************/
void MeshContainer::DrawWireframe(bool InDesingMode)
{
	D3DMATERIAL9 matDef;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���C���[�t���[���`��t���O
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�}�e���A���ޔ�
	pDevice->GetMaterial(&matDef);

	//DrawSurfaceNum += 100;
	//DrawSurfaceNum %= TotalSurfaceNum;

	// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(MeshFVF);

	//pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_3D));
	//pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | 1);

	//pDevice->SetIndices(IndexBuffer);

	//pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_BILLBOARD));
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh->GetNumVertices(), 0, mesh->GetNumFaces());
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, TotalSurfaceNum, VertexBuffer, sizeof(VERTEX_2D));

	//for (DWORD i = 0; i < TotalSurfaceNum; i++)
	//{
	//	//pDevice->SetTexture(0, textureContainer[i]);
	//	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * i, NUM_POLYGON);
	//}
	
#if 1
	for (DWORD i = 0; i < materialNum; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, textures[i]);

		//�}�e���A���ݒ�
		pDevice->SetMaterial(&materials[i]);

		//�`��
		mesh->DrawSubset(i);
	}
#endif

	//�}�e���A������
	pDevice->SetMaterial(&matDef);

	// ���C���[�t���[���I������
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}


/**************************************
�}�e���A�����擾����
***************************************/
UINT MeshContainer::GetMaterialNum()
{
	return materialNum;
}

/**************************************
�}�e���A���擾����
***************************************/
void MeshContainer::GetMaterial(UINT index, D3DMATERIAL9& out)
{
	assert(index >= 0 && index < materialNum);
	out = materials[index];
}

/**************************************
�}�e���A���J���[�ݒ菈��
***************************************/
void MeshContainer::SetMaterialColor(const D3DXCOLOR& color, UINT index)
{
	assert(index >= 0 && index < materialNum);

	materials[index].Diffuse = color;

}

/**************************************
�}�e���A���A���t�@�ݒ菈��
***************************************/
void MeshContainer::SetMaterialAlpha(float alpha, UINT index)
{
	assert(index >= 0 && index < materialNum);
	materials[index].Diffuse.a = alpha;
}

/**************************************
���C���[�t���[���p�p�����[�^�ݒ菈��
***************************************/
void MeshContainer::SetWireframePara()
{
	TotalSurfaceNum = mesh->GetNumFaces();
	MeshFVF = mesh->GetFVF();
	mesh->GetVertexBuffer(&VertexBuffer);
	mesh->GetIndexBuffer(&IndexBuffer);
}

/**************************************
���\�[�X�J������
***************************************/
void MeshContainer::ReleaseResource()
{
	SAFE_RELEASE(mesh);

	for (DWORD i = 0; i < materialNum; i++)
	{
		SAFE_RELEASE(textures[i]);
	}

	materials.clear();

	materialNum = 0;

	if (resource != NULL)
	{
		resource->OnRelease();
		resource = NULL;
	}
}
