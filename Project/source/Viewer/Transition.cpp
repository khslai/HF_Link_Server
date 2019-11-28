//=============================================================================
//
// �g�����W�V�����N���X [Transition.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "Transition.h"
#include "Framework/TextureDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../Camera/FieldCamera.h"

#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Math/TMath.h"
#include "../../Framework/Resource/ResourceManager.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
Transition::Transition() :
	ScreenObject(SCREEN_WIDTH, SCREEN_HEIGHT),
	effect(nullptr),
	Texture(nullptr),
	Active(false),
	CountFrame(0)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	//�G�t�F�N�g�ǂݍ���
	ResourceManager::Instance()->GetEffect("data/EFFECT/FlashEffect.cfx", effect);

	// �n���h���擾
	hFlashColor = effect->GetParameterByName(0, "FlashColor");
	effect->SetFloatArray(hFlashColor, (float*)&D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Transition::~Transition()
{
	SAFE_RELEASE(effect);
	SAFE_RELEASE(Texture);
}

//=============================================================================
// �X�V
//=============================================================================
void Transition::Update(void)
{
	if (!Active)
		return;

	CountFrame++;
	float T = (float)CountFrame / 60;
	Color = Easing::EaseValue(T, Vector3::Zero, Vector3::One, EaseType::InQuart);

	if (CountFrame >= 60)
	{
		Active = false;
	}
}

//=============================================================================
// �`��
//=============================================================================
void Transition::Draw(void)
{
	if (!Active)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetTexture(0, Texture);

	effect->Begin(0, 0);
	effect->BeginPass(0);

	effect->SetFloatArray(hFlashColor, (float*)&Color, 3);
	effect->CommitChanges();
	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
void Transition::LoadTexture(const LPDIRECT3DTEXTURE9 & Texture)
{
	if (this->Texture != nullptr)
	{
		SAFE_RELEASE(this->Texture);
	}
	this->Texture = Texture;
}

//=============================================================================
// �g�����W�V�����ݒu
//=============================================================================
void Transition::SetTransition(int Type, const LPDIRECT3DTEXTURE9& Texture)
{
	if (this->Texture != nullptr)
	{
		SAFE_RELEASE(this->Texture);
	}
	this->Texture = Texture;

	CountFrame = 0;
	// ���Z����J���[
	Color = Vector3::Zero;
	Active = true;
}
