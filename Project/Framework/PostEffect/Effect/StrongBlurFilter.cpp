//=====================================
//
//�X�g�����O�u���[�t�B���^����[StrongBlurFilter.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "StrongBlurFilter.h"
#include "../../Resource/ResourceManager.h"

/**************************************
�}�N����`
***************************************/
#define STRONGBLUR_ARRAY_SIZE		(9)

/**************************************
�N���X��`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
StrongBlurFilter::StrongBlurFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/EFFECT/StrongBlurFilter.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	hTexelU = effect->GetParameterByName(0, "texelU");
	hTexelV = effect->GetParameterByName(0, "texelV");
	effect->SetTechnique("tech");

	float u[STRONGBLUR_ARRAY_SIZE], v[STRONGBLUR_ARRAY_SIZE];
	for (int i = 0; i < STRONGBLUR_ARRAY_SIZE; i++)
	{
		u[i] = 1.0f / width * (i + 1);
		v[i] = 1.0f / height * (i + 1);
	}

	effect->SetFloatArray(hTexelU, u, STRONGBLUR_ARRAY_SIZE);
	effect->SetFloatArray(hTexelV, v, STRONGBLUR_ARRAY_SIZE);
	effect->CommitChanges();
}

/**************************************
�f�X�g���N�^
***************************************/
StrongBlurFilter::~StrongBlurFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void StrongBlurFilter::DrawEffect(UINT pass)
{
	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}