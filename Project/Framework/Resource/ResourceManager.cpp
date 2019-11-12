//=====================================
//
//���\�[�X�}�l�[�W������[ResourceManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResourceManager.h"
#include "../Renderer3D/MeshContainer.h"
#include "../Renderer3D/BoardPolygon.h"

#include "MeshResource.h"
#include "PolygonResource.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���b�V���ǂݍ��ݏ���
***************************************/
void ResourceManager::LoadMesh(const char* tag, const char* path)
{
	std::string tagStr = tag;

	//�^�O�̏d���m�F
	if (meshPool.count(tagStr) != 0)
		SAFE_DELETE(meshPool[tagStr]);

	//���b�V�����\�[�X�𐶐�
	meshPool[tagStr] = new MeshResource(path);
}

/**************************************
���b�V���������
***************************************/
void ResourceManager::ReleaseMesh(const char* tag)
{
	std::string tagStr = tag;

	//�^�O�̓o�^�m�F
	if (meshPool.count(tagStr) == 0)
		return;

	//���b�V���R���e�i���폜
	SAFE_DELETE(meshPool[tagStr]);
	meshPool.erase(tagStr);
}

/**************************************
���b�V���擾����
***************************************/
bool ResourceManager::GetMesh(const char* tag, MeshContainer* pOut)
{
	std::string tagStr = std::string(tag);

	//�o�^�m�F
	if (meshPool.count(tagStr) == 0)
		return false;

	//���b�V���ւ̎Q�Ƃ��i�[
	meshPool[tagStr]->Clone(pOut);
	return true;
}

/**************************************
�e�N�X�`���ǂݍ��ݏ���
***************************************/
void ResourceManager::LoadTexture(const char* path)
{
	std::string tagStr = path;

	//�d���m�F
	if (texturePool.count(tagStr) != 0)
		return;

	//�ǂݍ���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, path, &texturePool[tagStr]);
}

/**************************************
�e�N�X�`���������
***************************************/
void ResourceManager::ReleaseTexture(const char* tag)
{
	std::string tagStr = tag;

	//�o�^�m�F
	if (texturePool.count(tagStr) == 0)
		return;

	SAFE_RELEASE(texturePool[tagStr]);
}

/**************************************
�e�N�X�`���Q�Ə���
***************************************/
bool ResourceManager::GetTexture(const char* path, LPDIRECT3DTEXTURE9& pOut)
{
	std::string tagStr = path;

	//�o�^�m�F
	if (texturePool.count(tagStr) == 0)
	{
		LoadTexture(path);
	}

	pOut = texturePool[tagStr];

	if(pOut != NULL)
		pOut->AddRef();

	return true;
}

/**************************************
�|���S���쐬����
***************************************/
void ResourceManager::MakePolygon(const char* tag, const char* path, const D3DXVECTOR2& size, const D3DXVECTOR2& uv)
{
	std::string tagStr = std::string(tag);

	//�o�^�m�F
	if (polygonPool.count(tagStr) != 0)
		return;

	//BoardPolygon�N���X�𐶐����ēo�^
	PolygonResource *ptr = new PolygonResource(size, uv, path);
	polygonPool[tagStr] = ptr;
}

/**************************************
�|���S���������
***************************************/
void ResourceManager::ReleasePolygon(const char* tag)
{
	std::string tagStr = std::string(tag);

	//�o�^�m�F
	if (polygonPool.count(tagStr) == 0)
		return;

	SAFE_DELETE(polygonPool[tagStr]);
}

/**************************************
�G�t�F�N�g�ǂݍ��ݏ���
***************************************/
void ResourceManager::LoadEffect(const char * path)
{
	std::string tagStr = std::string(path);

	//�d���m�F
	if (effectPool.count(tagStr) != 0)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, path, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effectPool[tagStr], 0);
}

/**************************************
�G�t�F�N�g�������
***************************************/
void ResourceManager::ReleaseEffect(const char * path)
{
	std::string tagStr = std::string(path);

	//�o�^�m�F
	if (effectPool.count(tagStr) == 0)
		return;

	SAFE_RELEASE(effectPool[tagStr]);
}

/**************************************
�|���S���Q�Ə���
***************************************/
bool ResourceManager::GetPolygon(const char* tag, BoardPolygon* pOut)
{
	std::string tagStr = std::string(tag);

	//�o�^�m�F
	if (polygonPool.count(tagStr) == 0)
		return false;

	polygonPool[tagStr]->Clone(pOut);
	return true;
}

/**************************************
�G�t�F�N�g�擾����
***************************************/
bool ResourceManager::GetEffect(const char * path, LPD3DXEFFECT & pOut)
{
	std::string tagStr = std::string(path);

	//�o�^�m�F
	if (effectPool.count(tagStr) == 0)
		LoadEffect(path);

	pOut = effectPool[tagStr];
	pOut->AddRef();
	return true;
}

/**************************************
�S���\�[�X�������
***************************************/
void ResourceManager::AllRelease()
{
	for (auto& pair : meshPool)
	{
		SAFE_DELETE(pair.second);
	}
	meshPool.clear();

	for (auto& pair : texturePool)
	{
		SAFE_RELEASE(pair.second);
	}
	texturePool.clear();

	for (auto& pair : polygonPool)
	{
		SAFE_DELETE(pair.second);
	}
	polygonPool.clear();

	for (auto&& pair : effectPool)
	{
		SAFE_RELEASE(pair.second);
	}
	effectPool.clear();
}