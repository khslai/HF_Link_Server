//=====================================
//
//SkyBox.h
//�@�\:�X�J�C�{�b�N�X�w�b�_
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "../../main.h"

#include <vector>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SkyBox : public GameObject
{
public:
	//�ʂ�\��enum
	enum Surface
	{
		Up,
		Back,
		Down,
		Front,
		Left,
		Right,
		Max
	};

	//�R���X�g���N�^�A�f�X�g���N�^
	SkyBox(const D3DXVECTOR3& size);
	virtual ~SkyBox();

	//�`�揈��
	virtual void Draw();

	//�e�N�X�`���ǂݍ���
	virtual void LoadTexture(const char* fileName, Surface surface);

protected:
	//�e�N�X�`���R���e�i
	std::vector<LPDIRECT3DTEXTURE9> textureContainer;

	//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;

	//���_�o�b�t�@�쐬����
	virtual void MakeVertexBuffer(const float width, const float height, const float depth);
};

#endif