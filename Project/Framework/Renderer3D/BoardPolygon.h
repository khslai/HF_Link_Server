//=====================================
//
//�|���S���w�b�_[BoardPolygon.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOARDPOLYGON_H_
#define _BOARDPOLYGON_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/
class PolygonResource;
class SpriteEffect;

/**************************************
�N���X��`
***************************************/
class BoardPolygon
{
	friend class PolygonResource;
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	BoardPolygon();
	~BoardPolygon();

	//�`�揈��
	void Draw(const D3DXMATRIX& mtxWorld);

	//UV�����ݒ菈��
	void SetTexDiv(const D3DXVECTOR2& div);

	//�e�N�X�`���ʂ��ԍ��ݒ菈��
	void SetTextureIndex(int index);

	//�f�B�t���[�Y�ݒ菈��
	void SetDiffuse(const D3DXCOLOR& color);
	void SetAlpha(const float Alpha);
	D3DXCOLOR GetDiffuse(void) const;

protected:
	LPDIRECT3DDEVICE9 pDevice;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	PolygonResource *resource;

	SpriteEffect *effect;
};

#endif