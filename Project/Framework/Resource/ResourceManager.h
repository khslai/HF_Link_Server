//=====================================
//
//���\�[�X�}�l�[�W���w�b�_[ResourceManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "..\..\main.h"
#include "..\Pattern\BaseSingleton.h"
#include <unordered_map>

/**************************************
�O���錾
***************************************/
class MeshContainer;
class BoardPolygon;

class MeshResource;
class PolygonResource;

/**************************************
�N���X��`
***************************************/
class ResourceManager : public BaseSingleton<ResourceManager>
{
	friend class BaseSingleton<ResourceManager>;
public:
	//�ǂݍ��݁A�������
	void LoadMesh(const char* tag, const char* path);
	void ReleaseMesh(const char* tag);

	void LoadTexture(const char* path);
	void ReleaseTexture(const char* tag);

	void MakePolygon(const char* tag, const char* path, const D3DXVECTOR2& size, const D3DXVECTOR2& uv = D3DXVECTOR2(1.0f, 1.0f));
	void ReleasePolygon(const char* tag);

	void LoadEffect(const char* path);
	void ReleaseEffect(const char* path);

	//���\�[�X�Q�Ə���
	bool GetMesh(const char* tag, MeshContainer*  pOut);
	bool GetTexture(const char* path, LPDIRECT3DTEXTURE9& pOut);
	bool GetPolygon(const char* tag, BoardPolygon* pOut);
	bool GetEffect(const char* path, LPD3DXEFFECT& pOut);

	//�S���\�[�X�������
	void AllRelease();

private:
	ResourceManager() {}
	~ResourceManager() {}

	std::unordered_map<std::string, MeshResource*> meshPool;
	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> texturePool;
	std::unordered_map<std::string, PolygonResource*> polygonPool;
	std::unordered_map<std::string, LPD3DXEFFECT> effectPool;
};

#endif