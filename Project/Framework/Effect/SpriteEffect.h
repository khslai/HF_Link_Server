//=====================================
//
//SpriteEffect.h
//�@�\:�X�v���C�g�`��p�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPRITEEFFECT_H_
#define _SPRITEEFFECT_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SpriteEffect
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	SpriteEffect(const D3DXVECTOR2& texDiv = { 1.0f, 1.0f });
	~SpriteEffect();

	//�`��J�n�A�I���錾
	void Begin();
	void BeginPass(DWORD pass);
	void EndPass();
	void End();

	//�ύX���f����
	void Commit();

	//���[���h�ϊ��s��ݒ菈��
	void SetWorld(const D3DXMATRIX& mtxWorld);

	//�f�B�t���[�Y�ݒ菈��
	void SetDiffuse(const D3DXCOLOR& color);

	//�e�N�X�`���������ݒ菈��
	void SetTextureDivine(const D3DXVECTOR2& divine);

	//�e�N�X�`���ʂ��ԍ��ݒ菈��
	void SetTextureIndex(int index);

	//�r���[�s��ݒ菈��
	static void SetView(const D3DXMATRIX& mtx);

	//�v���W�F�N�V�����s��ݒ菈��
	static void SetProjection(const D3DXMATRIX& mtx);

	//�X�N���[�����e�s��ݒ菈��
	static void SetScreenProjection(const D3DXMATRIX& mtx);
		
private:
	LPD3DXEFFECT effect;				//�V�F�[�_�G�t�F�N�g

	D3DXCOLOR diffuse;					//�f�B�t���[�Y
	D3DXVECTOR2 texDiv;					//�e�N�X�`��������
	D3DXVECTOR2 texSize;				//���������e�N�X�`���̃T�C�Y
	D3DXVECTOR2 uv;						//UV���W

	static D3DXMATRIX mtxView;			//�r���[�s��
	static D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����s��
	static D3DXMATRIX mtxScreenProj;	//�X�N���[�����e�s��

	//�V�F�[�_�ւ̃n���h��
	D3DXHANDLE hMtxWorld;				
	D3DXHANDLE hMtxView;
	D3DXHANDLE hMtxProj;
	D3DXHANDLE hMtxScreenProj;
	D3DXHANDLE hTexUV;
	D3DXHANDLE hDiffuse;
};
#endif