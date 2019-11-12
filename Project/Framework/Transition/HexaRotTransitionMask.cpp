//=====================================
//
//�w�L�T�g�����W�V��������[HexaRotTransitionMask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "HexaRotTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"
#include "../Tween/Tween.h"

/**************************************
�}�N����`
***************************************/
#define HEXATRANSITION_DURATION		(60)

/**************************************
�R���X�g���N�^
***************************************/
HexaRotTransitionMask::HexaRotTransitionMask()
{
	//�|���S��������
	hex = new RotationHexa();
	hex->LoadTexture("data/TRANSITION/HexaMask.png");
	hex->SetSize((float)SCREEN_WIDTH, (float)SCREEN_WIDTH);
	hex->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f));
}

/**************************************
�f�X�g���N�^
***************************************/
HexaRotTransitionMask::~HexaRotTransitionMask()
{
	SAFE_DELETE(hex);
}

/**************************************
�X�V����
***************************************/
MaskResult HexaRotTransitionMask::Update()
{
	if (!active)
		return Continuous;

	MaskResult result = MaskResult::Continuous;

	cntFrame++;

	hex->Update();

	//�g�����W�V�����̏I���m�F
	if (cntFrame == HEXATRANSITION_DURATION)
	{
		//�}�X�N���I�t��
		active = false;
		
		result = isTransitionOut ? FinishTransitionOut : FinishTransitionIn;
	}
	return result;
}

/**************************************
�g�����W�V�����J�n����
***************************************/
void HexaRotTransitionMask::Draw()
{
	if (!active)
		return;

	BeginMask();

	hex->Draw();

	EndMask();
}

/**************************************
�g�����W�V�����J�n����
***************************************/
void HexaRotTransitionMask::Set(bool isTransitionOut)
{
	//���łɃ}�X�N���ł���ΊJ�n���Ȃ�
	if (active)
		return;

	//�C�[�W���O�J�n
	hex->Init(isTransitionOut);

	//�t���O������
	cntFrame = 0;
	active = true;
	this->isTransitionOut = isTransitionOut;
}

/**************************************
��]�Z�p�`����������
***************************************/
void RotationHexa::Init(bool isTransitionOut)
{
	const D3DXVECTOR3 InitScale = isTransitionOut ? Vector3::Zero : Vector3::One;
	const D3DXVECTOR3 EndScale = Vector3::One - InitScale;
	const EaseType Type = isTransitionOut ? EaseType::InExpo : EaseType::OutExpo;

	Tween::Scale(*this, InitScale, EndScale, HEXATRANSITION_DURATION, Type);
}

/**************************************
��]�Z�p�`�X�V����
***************************************/
void RotationHexa::Update()
{
	transform->Rotate(0.0f, 0.0f, 10.0f);
}