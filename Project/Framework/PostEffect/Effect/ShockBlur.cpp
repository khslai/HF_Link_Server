//=====================================
//
//�V���b�N�u���[����[ShockBlur.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ShockBlur.h"
#include "../../Resource/ResourceManager.h"

/**************************************
�}�N����`
***************************************/
#define EFFECTFILE_SHOCKBLUR_PATH	"PostEffect/ShockBlur.fx"
#define PRECOMPILE_SHOCKBLUR_PATH	"data/EFFECT/ShockBlur.cfx"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ShockBlur::ShockBlur(DWORD width, DWORD height) :
	ScreenObject(width, height),
	texelU(1.0f / width),
	texelV(1.0f / height)
{
	const char* Path = "data/EFFECT/ShockBlur.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	hndlPower = effect->GetParameterByName(0, "blurPower");
	hndlCenter = effect->GetParameterByName(0, "centerTexel");
	hndlTU = effect->GetParameterByName(0, "tU");
	hndlTV = effect->GetParameterByName(0, "tV");
}

/**************************************
�f�X�g���N�^
***************************************/
ShockBlur::~ShockBlur()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void ShockBlur::DrawEffect()
{
	effect->SetFloat(hndlTU, texelU);
	effect->SetFloat(hndlTV, texelV);
	effect->CommitChanges();

	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�p���[�Z�b�g����
***************************************/
void ShockBlur::SetPower(float power)
{
	effect->SetFloat(hndlPower, power);
	effect->CommitChanges();
}

/**************************************
�Z���^�[�Z�b�g����
***************************************/
void ShockBlur::SetCenterPos(const D3DXVECTOR3& pos)
{
	D3DXMATRIX view, projection;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVIEWPORT9 viewPort;
	D3DXVECTOR3 center;

	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetViewport(&viewPort);

	D3DXVec3TransformCoord(&center, &pos, &view);
	D3DXVec3TransformCoord(&center, &center, &projection);
	center.x = (center.x + 1.0f) / 2.0f;
	center.y = (-center.y + 1.0f) / 2.0f;

	effect->SetFloatArray(hndlCenter, (float*)&center, 2);
	effect->CommitChanges();

}