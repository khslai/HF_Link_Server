//=====================================
//
//�u���[���t�B���^�[����[BloomFilter.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BloomFilter.h"
#include "../../Resource/ResourceManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BloomFilter::BloomFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const char* Path = "data/EFFECT/BloomFilter.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	hThrethold = effect->GetParameterByName(0, "threthold");
	hBloomPower = effect->GetParameterByName(0, "bloomPower");
}

/**************************************
�f�X�g���N�^
***************************************/
BloomFilter::~BloomFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void BloomFilter::DrawEffect(UINT pass)
{
	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�������l�ݒ菈��
***************************************/
void BloomFilter::SetThrethold(float threthold)
{
	effect->SetFloat(hThrethold, threthold);
	effect->CommitChanges();
}

/**************************************
�Q�C���ݒ菈��
***************************************/
void BloomFilter::SetBloomPower(float power)
{
	effect->SetFloat(hBloomPower, power);
	effect->CommitChanges();
}