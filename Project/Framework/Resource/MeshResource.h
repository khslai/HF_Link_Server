//=====================================
//
//MeshResource.h
//�@�\:���b�V�����\�[�X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MESHRESOURCE_H_
#define _MESHRESOURCE_H_

#include "../../main.h"
#include <string>
#include <vector>

/**************************************
�O���錾
***************************************/
class MeshContainer;

/**************************************
�N���X��`
***************************************/
class MeshResource
{
public:
	MeshResource(const std::string& path);
	~MeshResource();

	void Clone(MeshContainer* container);
	void OnRelease();

private:
	LPD3DXMESH mesh;
	std::vector<D3DMATERIAL9> materials;
	std::vector<LPDIRECT3DTEXTURE9> textures;
	DWORD materialNum;

	unsigned cntRef;
};
#endif