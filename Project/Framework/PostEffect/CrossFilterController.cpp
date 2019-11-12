//=====================================
//
//�N���X�t�B���^�R���g���[������[CrossFilterController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "CrossFilterController.h"
#include "Effect/BloomFilter.h"
#include "Effect/CrossBlurFilter.h"
#include "../Tool/DebugWindow.h"

//#define DEBUG_CROSSFILTER
/**************************************
static�����o
***************************************/
const float CrossFilterController::DefaultPower = 1.0f;
const float CrossFilterController::DefaultThrethold = 0.0f;

/**************************************
�R���X�g���N�^
***************************************/
CrossFilterController::CrossFilterController() :
	bloomPower(),
	bloomThrethold()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�p���[�Ƃ������l�̏�����
	bloomPower[0] = bloomPower[1] = bloomPower[2] = DefaultPower;
	bloomThrethold[0] = bloomThrethold[1] = bloomThrethold[2] = DefaultThrethold;

	//�k���o�b�t�@�̕��ƍ������v�Z
	for (int i = 0; i < NumReduction; i++)
	{
		int reduction = (int)pow(2.0f, i + 2.0f);
		reducedWidth[i] = SCREEN_WIDTH / reduction;
		reducedHeight[i] = SCREEN_HEIGHT / reduction;
	}

	//�u���[���t�B���^�쐬
	for (int i = 0; i < 3; i++)
	{
		bloomFilter[i] = new BloomFilter(reducedWidth[i], reducedHeight[i]);
	}

	//�u���[�t�B���^�쐬
	for (int i = 0; i < 3; i++)
	{
		blurFilter[i] = new CrossBlurFilter(reducedWidth[i], reducedHeight[i]);
	}

	//�e�N�X�`���A�T�[�t�F�C�X��ݒ�
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pDevice->CreateTexture(reducedWidth[i], reducedHeight[i], 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &blurTexture[i][j], 0);
			blurTexture[i][j]->GetSurfaceLevel(0, &blurSurface[i][j]);
		}

		//�u���[�t�B���^�p�̃r���[�|�[�g��ݒ�
		blurViewPort[i].Width = reducedWidth[i];
		blurViewPort[i].Height = reducedHeight[i];
		blurViewPort[i].X = 0;
		blurViewPort[i].Y = 0;
		blurViewPort[i].MinZ = 0.0f;
		blurViewPort[i].MaxZ = 1.0f;
	}
}
/**************************************
�f�X�g���N�^
***************************************/
CrossFilterController::~CrossFilterController()
{
	for (int i = 0; i < NumReduction; i++)
	{
		for (int j = 0; j < NumBlur; j++)
		{
			SAFE_RELEASE(blurTexture[i][j]);
			SAFE_RELEASE(blurSurface[i][j]);
		}

		SAFE_DELETE(bloomFilter[i]);
		SAFE_DELETE(blurFilter[i]);
	}
}

/**************************************
�`�揈��
***************************************/
void CrossFilterController::Draw(LPDIRECT3DTEXTURE9 targetTexture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�u���[����������̂ŃT���v�����O��CLAMP�ɐݒ�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//Z�o�b�t�@�ւ̏������݂��s��Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//�r���[�|�[�g��ޔ�
	pDevice->GetViewport(&oldViewPort);

	//�����_�[�^�[�Q�b�g��ޔ�
	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);

	//�P�x���o����
	SampleBrightness(targetTexture);

	//���o�����P�x���u���[����(
	ProcessBlur();

	//�����_�[�^�[�Q�b�g�����ɖ߂�
	pDevice->SetRenderTarget(0, oldSuf);

	//�N���X�t�B���^����
	BlendBloom();

	//�����_�[�^�[�Q�b�g�̎Q�Ƃ����
	SAFE_RELEASE(oldSuf);

	//Z�o�b�t�@�ɏ������ނ悤�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//�T���v�����O�����ɖ߂�
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

#ifdef DEBUG_CROSSFILTER
	Debug::Begin("CrossFilter");
	for (int i = 0; i < 3; i++)
	{
		Debug::DrawTexture(blurTexture[i][0], { 200.0f, 100.0f });
		Debug::SameLine();
	}
	Debug::End();
#endif
}

/**************************************
�p���[�ݒ菈��
***************************************/
void CrossFilterController::SetPower(float power1, float power2, float power3)
{
	bloomPower[0] = power1;
	bloomPower[1] = power2;
	bloomPower[2] = power3;
}

/**************************************
�������l�ݒ菈��
***************************************/
void CrossFilterController::SetThrethold(float threthold1, float threthold2, float threthold3)
{
	bloomThrethold[0] = threthold1;
	bloomThrethold[1] = threthold2;
	bloomThrethold[2] = threthold3;
}

/**************************************
�P�x���o����
***************************************/
void CrossFilterController::SampleBrightness(LPDIRECT3DTEXTURE9 targetTexture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < 3; i++)
	{
		//�����_�[�^�[�Q�b�g��ݒ肵�N���A
		pDevice->SetRenderTarget(0, blurSurface[i][0]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);

		//�r���[�|�[�g��ݒ�
		pDevice->SetViewport(&blurViewPort[i]);

		//�u���[���̃p�����[�^��ݒ�
		bloomFilter[i]->SetBloomPower(bloomPower[i]);
		bloomFilter[i]->SetThrethold(bloomThrethold[i]);

		pDevice->SetTexture(0, targetTexture);

		bloomFilter[i]->DrawEffect(0);
	}
}

/**************************************
�u���[����
***************************************/
void CrossFilterController::ProcessBlur()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const int PassMax = 4;
	const int TextureMax = 2;

	//�u���[�p�̃T�[�t�F�C�X���N���A
	for (int i = 0; i < 3; i++)
	{
		pDevice->SetRenderTarget(0, blurSurface[i][1]);
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0, 0);
	}

	for (int j = 0; j < 3; j++)
	{
		//�r���[�|�[�g��ݒ�
		pDevice->SetViewport(&blurViewPort[j]);

		//�u���[����
		const int BlurLoop = 8;
		for (cntBlur = 0; cntBlur < BlurLoop; cntBlur++)
		{
			pDevice->SetRenderTarget(0, blurSurface[j][(cntBlur + 1) % TextureMax]);
			pDevice->SetTexture(0, blurTexture[j][cntBlur % TextureMax]);
			blurFilter[j]->DrawEffect(cntBlur % PassMax);
		}
	}

	//�r���[�|�[�g�����Ƃɖ߂�
	pDevice->SetViewport(&oldViewPort);
}

/**************************************
��������
***************************************/
void CrossFilterController::BlendBloom()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�|�[�g�����Ƃɖ߂�
	pDevice->SetViewport(&oldViewPort);

	//�����_�[�X�e�[�g�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	for (int i = 0; i < NumReduction; i++)
	{
		pDevice->SetTexture(0, blurTexture[0][cntBlur % 2]);
		renderer->Draw();
	}

	//�����_�[�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}