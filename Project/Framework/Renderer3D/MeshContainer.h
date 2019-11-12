//=====================================
//
//���b�V���R���e�i�w�b�_[MeshContainer.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MESHCONTAINER_H_
#define _MESHCONTAINER_H_

#include "../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class MeshResource;

/**************************************
�N���X��`
***************************************/
class MeshContainer
{
	friend class MeshResource;
public:
	MeshContainer();					//�R���X�g���N�^
	~MeshContainer();					//�f�X�g���N�^

	void Draw();							//���f����`��
	void DrawWireframe(bool InDesingMode);	//���f���̃��C���[�t���[����`��

	UINT GetMaterialNum();
	void GetMaterial(UINT index, D3DMATERIAL9& out);
	void SetMaterialColor(const D3DXCOLOR& color, UINT index);
	void SetMaterialAlpha(float alpha, UINT index);
	void SetWireframePara();

protected:								
	LPD3DXMESH mesh;								//���b�V���f�[�^
	std::vector<D3DMATERIAL9> materials;			//�}�e���A�����
	std::vector<LPDIRECT3DTEXTURE9> textures;		//�e�N�X�`��
	DWORD materialNum;								//�}�e���A����

private:
	MeshResource * resource;						//���\�[�X�̎Q�ƌ�
	bool initialized;								//���b�V�����������ς݂��ǂ���
	DWORD TotalSurfaceNum;							//�`�悷��ʂ̐�
	DWORD DrawSurfaceNum;							//�`�悷��ʂ̐�
	DWORD MeshFVF;
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
	LPDIRECT3DINDEXBUFFER9 IndexBuffer;

	void ReleaseResource();							//���\�[�X�������
};

#endif