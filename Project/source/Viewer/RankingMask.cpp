//=============================================================================
//
// �����L���O�}�X�N�N���X [RankingMask.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "RankingMask.h"

#include "../../Framework/Math/Easing.h"

/**************************************
�}�N����`
***************************************/


/**************************************
�R���X�g���N�^
***************************************/
RankingMask::RankingMask(D3DXVECTOR3 Pos)
{
	//�|���S��������
	rect = new RectangleMask();
	rect->LoadTexture("data/TRANSITION/RectangleMask.png");
	rect->SetSize((float)SCREEN_WIDTH / 2, 120.0f);
	rect->SetPosition(Pos);
}

/**************************************
�f�X�g���N�^
***************************************/
RankingMask::~RankingMask()
{
	SAFE_DELETE(rect);
}

/**************************************
�X�V����
***************************************/
MaskResult RankingMask::Update()
{
	if (!active)
		return Continuous;

	MaskResult result = MaskResult::Continuous;

	cntFrame++;

	rect->Update();

	//�g�����W�V�����̏I���m�F
	//if (cntFrame == 120)
	//{
	//	// �}�X�N���I�t��
	//	active = false;

	//	result = isTransitionOut ? FinishTransitionOut : FinishTransitionIn;
	//}
	return result;
}

/**************************************
�g�����W�V�����J�n����
***************************************/
void RankingMask::Draw()
{
	if (!active)
		return;

	BeginMask();

	rect->Draw();

	EndMask();
}



/**************************************
�g�����W�V�����J�n����
***************************************/
void RankingMask::Set(void)
{
	//���łɃ}�X�N���ł���ΊJ�n���Ȃ�
	if (active)
		return;

	//�C�[�W���O�J�n
	rect->Init();

	//�t���O������
	cntFrame = 0;
	active = true;
}

/**************************************
�g�����W�V�����J�n����
***************************************/
void RankingMask::Set(bool isTransitionOut)
{
}

//=====================================================
// RectangleMask Class
//=====================================================
/**************************************
��]�Z�p�`����������
***************************************/
void RectangleMask::Init(void)
{
	const D3DXVECTOR3 InitScale =  Vector3::One;
	const D3DXVECTOR3 EndScale = Vector3::One - InitScale;
	const EaseType Type = EaseType::InQuart;

	//Tween::Scale(*this, InitScale, EndScale, HEXATRANSITION_DURATION, Type);
}

/**************************************
��]�Z�p�`�X�V����
***************************************/
void RectangleMask::Update()
{
	//transform->Rotate(0.0f, 0.0f, 10.0f);
}

