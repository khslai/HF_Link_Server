//=====================================
//
//�X�p�C�N�m�C�Y�R���g���[������[SpikeNoiseController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpikeNoiseController.h"
#include "Effect\SpikeNoise.h"
#include "../Math/Easing.h"

/**************************************
�}�N����`
***************************************/
#define USE_SPIKENOISECTRL_DEBUG

#define SPIKENOISE_SCROLL_SPEED	(0.001f)

/**************************************
�R���X�g���N�^
***************************************/
SpikeNoiseController::SpikeNoiseController()
{
	//�X�p�C�N�m�C�Y�̃C���X�^���X�𐶐�
	spikeNoise = new SpikeNoise(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�e�N�X�`�����쐬���T�[�t�F�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture, 0);
	texture->GetSurfaceLevel(0, &surface);
}

/**************************************
�f�X�g���N�^
***************************************/
SpikeNoiseController::~SpikeNoiseController()
{
	//���
	delete spikeNoise;
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}

/**************************************
�Z�b�g����
***************************************/
void SpikeNoiseController::SetNoise(float power, int effectTime)
{
	if (active)
		return;

	this->active = true;
	this->cntFrame = 0;
	this->effectTime = effectTime;
	this->state = State::Start;
	this->destPower = power;
	this->srcPower = 0.0f;
	this->base = 0.0f;
}

/**************************************
�X�V����
***************************************/
void SpikeNoiseController::Update()
{
	if (!active)
		return;

	cntFrame++;

	//�m�C�Y���X�N���[��
	base = Math::WrapAround(0.0f, 1.0f, base + SPIKENOISE_SCROLL_SPEED);
	spikeNoise->SetBaseY(base);

	//�e�X�e�[�g�X�V����
	if (state == State::Start)
		OnStart();
	else if (state == State::Wait)
		OnWait();
	else
		OnEnd();

	//�h���[�t���O�𗧂Ă�
	this->drawFlag = true;
}

/**************************************
Start�X�V����
***************************************/
void SpikeNoiseController::OnStart()
{
	const int Duration = 10;

	//�m�C�Y�̋������A�j���[�V����
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, this->srcPower, this->destPower, EaseType::InCubic);
	this->spikeNoise->SetLength(power);

	//�J�ڔ���
	if (cntFrame == Duration)
	{
		state++;
		this->cntFrame = 0;
	}
}

/**************************************
Wait�X�V����
***************************************/
void SpikeNoiseController::OnWait()
{
	//�J�ڔ���
	if (cntFrame == effectTime)
	{
		state++;
		this->cntFrame = 0;
		srcPower = destPower;
		destPower = 0.0f;
	}
}

/**************************************
End�X�V����
***************************************/
void SpikeNoiseController::OnEnd()
{
	const int Duration = 10;

	//�m�C�Y�̋������A�j���[�V����
	float t = (float)cntFrame / (float)Duration;
	float power = Easing::EaseValue(t, this->srcPower, this->destPower, OutCubic);
	this->spikeNoise->SetLength(power);

	//�J�ڔ���
	if (cntFrame == Duration)
	{
		active = false;
	}
}

/**************************************
�`�揈��
***************************************/
void SpikeNoiseController::Draw(LPDIRECT3DTEXTURE9 targetTexture)
{
	//��A�N�e�B�u�ł���Α������^�[��
	if (!this->active)
		return;

	//�`��ς݂ł���Α������^�[��
	if (!this->drawFlag)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, surface);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	pDevice->SetTexture(0, targetTexture);
	spikeNoise->DrawEffect();

	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	pDevice->SetTexture(0, texture);
	spikeNoise->Draw();

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}
