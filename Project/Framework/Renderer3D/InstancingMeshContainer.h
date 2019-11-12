//=====================================
//
// InstancingMeshContainer.h
// �@�\:�C���X�^���V���O�p���b�V���R���e�i
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _INSTANCINGMESHCONTAINER_H_
#define _INSTANCINGMESHCONTAINER_H_

#include "../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class InstancingMeshEffect;

/**************************************
�N���X��`
***************************************/
class InstancingMeshContainer
{
	friend class MeshResource;
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	InstancingMeshContainer(unsigned MaxNum);
	~InstancingMeshContainer();

	//���\�[�X�ǂݍ��݌�̏���������
	void Load(const std::string& path);

	//�`�揈��
	void Draw();

	//���_�o�b�t�@���b�N�A�A�����b�N����
	void Lock();
	void Unlock();

	//SRT��񖄂ߍ��ݏ���
	bool EmbedTranform(const Transform& transform);

protected:
	const unsigned MaxInstance;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	DWORD fvf;
	LPDIRECT3DVERTEXDECLARATION9 declare;

	LPDIRECT3DVERTEXBUFFER9 transformBuffer;

	DWORD numMaterial;
	
	std::vector<D3DMATERIAL9> materials;
	std::vector<D3DXATTRIBUTERANGE> attributeTable;
	std::vector<LPDIRECT3DTEXTURE9> textures;

	InstancingMeshEffect *effect;

	D3DXMATRIX* pWorld;
	DWORD indexTransform;
	
	void MakeDeclaration(LPD3DXMESH mesh);
};

#endif