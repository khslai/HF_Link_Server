//=====================================
//
//�g�����W�V�����R���g���[������[TransitionController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TransitionController.h"
#include "BaseTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"

#include "HexaRotTransitionMask.h"
#include "HexaPopTransitionMask.h"
#include "MistTransitionMask.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
TransitionController::TransitionController()
{
	callback = NULL;

	transitionBG = new Polygon2D();
	transitionBG->LoadTexture("data/TRANSITION/Transition.jpg");
	transitionBG->SetSize(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
	transitionBG->SetPosition(D3DXVECTOR3((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, 0.0f));

	maskContainer.resize(TransitionType::TransitionMax);
	maskContainer[TransitionType::HexaRotation] = new HexaRotTransitionMask();
	maskContainer[TransitionType::HexaPop] = new HexaPopTransitionMask();
	maskContainer[TransitionType::Mist] = new MistTransitionMask();

	usingMask = TransitionType::HexaRotation;
}

/**************************************
�f�X�g���N�^
***************************************/
TransitionController::~TransitionController()
{
	Utility::DeleteContainer(maskContainer);
	SAFE_DELETE(transitionBG);
}

/**************************************
�X�V����
***************************************/
void TransitionController::Update()
{
	if (!isRunning)
		return;

	MaskResult res = maskContainer[usingMask]->Update();

	if (res != MaskResult::Continuous)
	{
		isRunning = false;

		if (callback != NULL)
		{
			callback();
		}

		if (res == MaskResult::FinishTransitionOut)
			isDrawBG = false;
	}
}

/**************************************
�}�X�N�`�揈��
***************************************/
void TransitionController::DrawMask()
{
	maskContainer[usingMask]->Draw();
}

/**************************************
�g�����W�V�����`�揈��
***************************************/
void TransitionController::DrawTransition()
{
	if (!isDrawBG)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

	transitionBG->Draw();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
}

/**************************************
�g�����W�V�����ݒ菈��
***************************************/
bool TransitionController::SetTransition(bool isOut, TransitionType type, function<void(void)> callback)
{
	if (isRunning)
		return false;

	this->callback = callback;
	usingMask = type;
	isDrawBG = true;
	isRunning = true;

	maskContainer[type]->Set(isOut);

	return true;
}