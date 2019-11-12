//=====================================
//
//�x�[�X�g�����W�V��������[BaseTransitionMask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BaseTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"

/**************************************
static�����o
***************************************/
const int BaseTransitionMask::FramePerSecond = 30;

/**************************************
�R���X�g���N�^
***************************************/
BaseTransitionMask::BaseTransitionMask()
{
	//�t���O������
	active = false;
	isTransitionOut = false;
}

/**************************************
�f�X�g���N�^
***************************************/
BaseTransitionMask::~BaseTransitionMask()
{

}

/**************************************
�}�X�N�J�n����
***************************************/
void BaseTransitionMask::BeginMask()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (!active)
		return;
	
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->Clear(0, 0, D3DCLEAR_STENCIL, 0, 0.0f, 0);
}

/**************************************
�}�X�N�I������
***************************************/
void BaseTransitionMask::EndMask()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
		D3DCOLORWRITEENABLE_RED |
		D3DCOLORWRITEENABLE_GREEN |
		D3DCOLORWRITEENABLE_BLUE |
		D3DCOLORWRITEENABLE_ALPHA);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}