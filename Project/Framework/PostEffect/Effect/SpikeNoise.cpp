//=====================================
//
//�X�p�C�N�m�C�Y����[SpikeNoise.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpikeNoise.h"
#include "../../Resource/ResourceManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
SpikeNoise::SpikeNoise(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/EFFECT/SpikeNoise.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	hndlLength = effect->GetParameterByName(0, "length");
	hBaseY = effect->GetParameterByName(0, "baseY");
}

/**************************************
�f�X�g���N�^
***************************************/
SpikeNoise::~SpikeNoise()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void SpikeNoise::DrawEffect()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�c�ݒ����Z�b�g����
***************************************/
void SpikeNoise::SetLength(float length)
{
	effect->SetFloat(hndlLength, length);
	effect->CommitChanges();
}

/**************************************
Y��_�Z�b�g����
***************************************/
void SpikeNoise::SetBaseY(float f)
{
	effect->SetFloat(hBaseY, f);
	effect->CommitChanges();
}