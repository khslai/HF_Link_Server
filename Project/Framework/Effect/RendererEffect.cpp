//=====================================
//
//�`��G�t�F�N�g����[RendererEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "RendererEffect.h"

/**************************************
static�ϐ�
***************************************/
D3DXMATRIX RendererEffect::mtxView;
D3DXMATRIX RendererEffect::mtxProjection;

/*************************************
�r���[�s��ݒ菈��
***************************************/
void RendererEffect::SetView(const D3DXMATRIX & viewMatrix)
{
	mtxView = viewMatrix;
}

/*************************************
�v���W�F�N�V�����s��ݒ菈��
***************************************/
void RendererEffect::SetProjection(const D3DXMATRIX & projectionMatrix)
{
	mtxProjection = projectionMatrix;
}

/**************************************
�ύX���f����
***************************************/
void RendererEffect::Commit()
{
	effect->CommitChanges();
}

/**************************************
�`��J�n�錾
***************************************/
void RendererEffect::Begin()
{
	CommitCameraParameter();
	effect->Begin(0, 0);
}

/**************************************
�p�X�J�n�錾
***************************************/
void RendererEffect::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
�p�X�I���錾
***************************************/
void RendererEffect::EndPass()
{
	effect->EndPass();
}

/**************************************
�`��I���錾
***************************************/
void RendererEffect::End()
{
	effect->End();
}