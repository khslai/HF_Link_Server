//=====================================
//
//���m�g�[���t�B���^����[MonotoneFilter.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MonotoneFilter.h"
#include "../../Math/TMath.h"
#include "../../Resource/ResourceManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
MonotoneFilter::MonotoneFilter(DWORD width, DWORD height) :
	ScreenObject(width, height)
{
	const char* Path = "data/Effect/MonotoneFilter.cfx";
	ResourceManager::Instance()->GetEffect(Path, effect);

	effect->SetTechnique("tech");
	hndlPower = effect->GetParameterByName(0, "power");
}

/**************************************
�f�X�g���N�^
***************************************/
MonotoneFilter::~MonotoneFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void MonotoneFilter::Draw()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�����ݒ菈��
***************************************/
void MonotoneFilter::SetPower(float power)
{
	effect->SetFloat(hndlPower, Math::Clamp(0.0f, 1.0f, power));
	effect->CommitChanges();
}