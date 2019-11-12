//=====================================
//
//�V���b�N�u���[�R���g���[������[ShockBlurController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ShockBlurController.h"
#include "../Math/Easing.h"

/**************************************
�}�N����`
***************************************/
#define SHOCKBLURCTRL_USE_DEBUG

/*************************************
�R���X�g���N�^
***************************************/
ShockBlurController::ShockBlurController()
{
	shockBlur = new ShockBlur(SCREEN_WIDTH, SCREEN_HEIGHT);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture, 0);
	texture->GetSurfaceLevel(0, &surface);
}

/**************************************
�f�X�g���N�^
***************************************/
ShockBlurController::~ShockBlurController()
{
	delete shockBlur;
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}

/**************************************
�X�V����
***************************************/
void ShockBlurController::Update()
{
	//��A�N�e�B�u�ł���Α������^�[��
	if (!active)
		return;

	cntFrame++;

	//�e�X�e�[�g�X�V����
	if (state == State::Start)
		OnStart();
	else if (state == State::Wait)
		OnWait();
	else
		OnEnd();

	//�h���[�t���O�𗧂Ă�
	drawFlag = true;
}

/**************************************
Start�X�V����
***************************************/
void ShockBlurController::OnStart()
{
	const int Duration = 10;

	//�u���[�̋������A�j���[�V����
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, srcPower, destPower, EaseType::InCubic);

	if (cntFrame == Duration)
	{
		cntFrame = 0;
		state++;
	}
}

/**************************************
Wait�X�V����
***************************************/
void ShockBlurController::OnWait()
{
	//�ҋ@�̂�

	if (cntFrame == effectTime)
	{
		cntFrame = 0;
		srcPower = destPower;
		destPower = 0.0f;
		state++;
	}
}

/**************************************
End�X�V����
***************************************/
void ShockBlurController::OnEnd()
{
	const int Duration = 10;

	//�u���[�̋������A�j���[�V����
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, srcPower, destPower, EaseType::OutCubic);

	if (cntFrame == Duration)
	{
		cntFrame = 0;
		active = false;
	}
}

/**************************************
�`�揈��
***************************************/
void ShockBlurController::Draw(LPDIRECT3DTEXTURE9 targetTexture)
{
	//��A�N�e�B�u�ł���Α������^�[��
	if (!active)
		return;

	//�`��ς݂ł���Α������^�[��
	if (!drawFlag)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, surface);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	pDevice->SetTexture(0, targetTexture);
	shockBlur->DrawEffect();

	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	pDevice->SetTexture(0, texture);
	shockBlur->Draw();

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
�G�t�F�N�g�Z�b�g����
***************************************/
void ShockBlurController::SetBlur(D3DXVECTOR3 pos, float power, int duration)
{
	//�A�N�e�B�u�ł���ꍇ�͏㏑�����Ȃ�
	if (active)
		return;

	active = true;
	srcPower = 0.0f;
	destPower = power;
	cntFrame = 0;
	state = State::Start;
	effectTime = duration;

	shockBlur->SetCenterPos(pos);
}