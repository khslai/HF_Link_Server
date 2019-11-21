//=============================================================================
//
// �w�i�N���X [Background.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "Background.h"
#include "TextureDrawer.h"
#include "../Effect/GameParticleManager.h"

#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Renderer3D/BoardPolygon.h"
#include "../../Framework/Resource/ResourceManager.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
Background::Background()
{
	ResourceManager::Instance()->MakePolygon("Background", "data/TEXTURE/Viewer/Background/Background.png", { 120.0f, 68.0f});
	BG = new BoardPolygon();
	ResourceManager::Instance()->GetPolygon("Background", BG);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
Background::~Background()
{
	SAFE_DELETE(BG);
}

//=============================================================================
// �X�V
//=============================================================================
void Background::Update(void)
{

}

//=============================================================================
// �`��
//=============================================================================
void Background::Draw(void)
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// �e�X�g�`��
	Transform transform = Transform(
		D3DXVECTOR3(0.0f, 10.0f, 100.0f),
		Vector3::Zero,
		Vector3::One);

	BG->Draw(transform.GetMatrix());

	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}