//=====================================
//
//PolygonResource.h
//�@�\:�|���S�����\�[�X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _POLYGONRESOURCE_H_
#define _POLYGONRESOURCE_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class BoardPolygon;

/**************************************
�N���X��`
***************************************/
class PolygonResource
{
public:
	PolygonResource(const D3DXVECTOR2& size, const D3DXVECTOR2& uv = { 0.0f, 0.0f}, const char* texturePath = nullptr);
	~PolygonResource();

	void Clone(BoardPolygon* entity);
	void OnRelease();

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	unsigned cntRef;
};

#endif