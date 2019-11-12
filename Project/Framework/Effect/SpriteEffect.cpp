//=====================================
//
//SpriteEffect.cpp
//�@�\:�X�v���C�g�`��p�G�t�F�N�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpriteEffect.h"
#include "../Resource/ResourceManager.h"

/**************************************
static�����o
***************************************/
D3DXMATRIX SpriteEffect::mtxView;
D3DXMATRIX SpriteEffect::mtxProjection;
D3DXMATRIX SpriteEffect::mtxScreenProj;

/**************************************
�R���X�g���N�^
***************************************/
SpriteEffect::SpriteEffect(const D3DXVECTOR2 & texDiv) :
	effect(nullptr),
	diffuse(1.0f, 1.0f, 1.0f, 1.0f),
	texDiv(texDiv),
	texSize(1.0f / texDiv.x, 1.0f / texDiv.y),
	uv(0.0f, 0.0f)
{
	//�G�t�F�N�g�ǂݍ���
	ResourceManager::Instance()->GetEffect("data/EFFECT/Sprite.cfx", effect);

	//�n���h���擾
	hMtxWorld = effect->GetParameterByName(0, "mtxWorld");
	hMtxView = effect->GetParameterByName(0, "mtxView");
	hMtxProj = effect->GetParameterByName(0, "mtxProj");
	hMtxScreenProj = effect->GetParameterByName(0, "mtxScreenProj");
	hTexUV = effect->GetParameterByName(0, "texUV");
	hDiffuse = effect->GetParameterByName(0, "diffuse");
}

/**************************************
�f�X�g���N�^
***************************************/
SpriteEffect::~SpriteEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
�J�n����
***************************************/
void SpriteEffect::Begin()
{
	effect->Begin(0, 0);
}

/**************************************
�p�X�J�n�V����
***************************************/
void SpriteEffect::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
�p�X�I������
***************************************/
void SpriteEffect::EndPass()
{
	effect->EndPass();
}

/**************************************
�I������
***************************************/
void SpriteEffect::End()
{
	effect->End();
}

/**************************************
�ύX���f����
***************************************/
void SpriteEffect::Commit()
{	
	effect->SetMatrix(hMtxView, &mtxView);
	effect->SetMatrix(hMtxProj, &mtxProjection);
	effect->SetMatrix(hMtxScreenProj, &mtxScreenProj);
	effect->SetFloatArray(hDiffuse, (float*)&diffuse, 4);
	effect->SetFloatArray(hTexUV, (float*)&uv, 2);
	effect->CommitChanges();
}

/**************************************
���[���h�ϊ��s��Z�b�g����
***************************************/
void SpriteEffect::SetWorld(const D3DXMATRIX & mtxWorld)
{
	effect->SetMatrix(hMtxWorld, &mtxWorld);
}

/**************************************
�f�B�t���[�Y�ݒ菈��
***************************************/
void SpriteEffect::SetDiffuse(const D3DXCOLOR & color)
{
	diffuse = color;
}

/**************************************
�e�N�X�`���������ݒ菈��
***************************************/
void SpriteEffect::SetTextureDivine(const D3DXVECTOR2 & divine)
{
	texDiv = divine;
	texSize.x = 1.0f / texDiv.x;
	texSize.y = 1.0f / texDiv.y;
}

/**************************************
�e�N�X�`���ʂ��ԍ��ݒ菈��
***************************************/
void SpriteEffect::SetTextureIndex(int index)
{
	int u = index % (int)texDiv.x;
	int v = index / (int)texDiv.x;

	uv.x = u * texSize.x;
	uv.y = v * texSize.y;
}

/**************************************
�r���[�s��ݒ菈��
***************************************/
void SpriteEffect::SetView(const D3DXMATRIX & mtx)
{
	mtxView = mtx;
}

/**************************************
�v���W�F�N�V�����s��ݒ菈��
***************************************/
void SpriteEffect::SetProjection(const D3DXMATRIX & mtx)
{
	mtxProjection = mtx;
}

/**************************************
�X�N���[�����e�s��ݒ菈��
***************************************/
void SpriteEffect::SetScreenProjection(const D3DXMATRIX & mtx)
{
	mtxScreenProj = mtx;
}
