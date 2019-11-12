//=====================================
//
//�~�X�g�g�����W�V�����}�X�N����[MistTransitionMask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "MistTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"

/**************************************
�}�N����`
***************************************/
#define MISTTRANSITION_ALPHAREF_MAX		(255.0f)
#define MISTRANSITION_DURATION			(60)
#define MISTTRANSITION_TEX_NAME			"data/TRANSITION/MistMask.png"

/**************************************
�R���X�g���N�^
***************************************/
MistTransitionMask::MistTransitionMask()
{
	//�|���S��������
	polygon = new Polygon2D();
	polygon->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	polygon->LoadTexture(MISTTRANSITION_TEX_NAME);
	polygon->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f));
}

/**************************************
�f�X�g���N�^
***************************************/
MistTransitionMask::~MistTransitionMask()
{
	SAFE_DELETE(polygon);
}

/**************************************
�X�V����
***************************************/
MaskResult MistTransitionMask::Update()
{
	if (!active)
		return MaskResult::Continuous;

	MaskResult res = MaskResult::Continuous;

	cntFrame++;

	float t = (float)cntFrame / MISTRANSITION_DURATION;
	alphaRef = (DWORD)Easing::EaseValue(t, startRef, endRef, type);

	if (cntFrame == MISTRANSITION_DURATION)
	{
		res = isTransitionOut ? MaskResult::FinishTransitionOut : MaskResult::FinishTransitionIn;
		active = false;
	}

	return res;
}

/**************************************
�`�揈��
***************************************/
void MistTransitionMask::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�}�X�N�J�n
	BeginMask();

	//���̃A���t�@�Q�ƒl��ۑ����؂�ւ�
	DWORD defAlphaRef;
	pDevice->GetRenderState(D3DRS_ALPHAREF, &defAlphaRef);
	pDevice->SetRenderState(D3DRS_ALPHAREF, alphaRef);

	//�}�X�N�̈�`��
	polygon->Draw();

	//�}�X�N�I��
	EndMask();

	//�A���t�@�Q�ƒl�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHAREF, defAlphaRef);
}

/**************************************
�Z�b�g����
***************************************/
void MistTransitionMask::Set(bool isOut)
{
	if (active)
		return;

	alphaRef = 0;
	cntFrame = 0;

	active = true;
	isTransitionOut = isOut;

	type = isOut ? EaseType::OutCubic : EaseType::OutCubic;
	startRef = isOut ? MISTTRANSITION_ALPHAREF_MAX : 0;
	endRef = MISTTRANSITION_ALPHAREF_MAX - startRef;
}
