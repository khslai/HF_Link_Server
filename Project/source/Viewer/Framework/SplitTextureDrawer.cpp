//=============================================================================
//
// �e�N�X�`���`��(��������)�N���X [SplitTextureDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include"../../../main.h"
#include "SplitTextureDrawer.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Math/Easing.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SplitTextureDrawer::SplitTextureDrawer(int DevideX, int DevideY, D3DXVECTOR2 TextureSize, bool Visible) :
	DevideX(DevideX),
	DevideY(DevideY),
	IndexX(0),
	IndexY(0)
{
	UnitUV.x = 1.0f / DevideX;
	UnitUV.y = 1.0f / DevideY;
	this->TextureSize.x = TextureSize.x / DevideX;
	this->TextureSize.y = TextureSize.y / DevideY;
	this->Visible = Visible;
	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
SplitTextureDrawer::~SplitTextureDrawer()
{
	SAFE_RELEASE(Texture);
}

//=============================================================================
// �X�V����
//=============================================================================
void SplitTextureDrawer::Update()
{
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void SplitTextureDrawer::MakeVertex()
{
	// ���_���W�̐ݒ�
	SetVertex();

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	// �e�N�X�`���F�̐ݒ�
	SetColor(SET_COLOR_NOT_COLORED);

	// �e�N�X�`�����W�̐ݒ�
	SetTexture();
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SplitTextureDrawer::SetVertex(void)
{
	// ���_���W�̐ݒ�
	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, TextureSize.y / 2, 0.0f);
}

//=============================================================================
// �e�N�X�`��UV�ݒ菈��
//=============================================================================
void SplitTextureDrawer::SetTexture()
{
	Vertex[0].tex = D3DXVECTOR2(IndexX * UnitUV.x, IndexY * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((IndexX + 1) * UnitUV.x, IndexY * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(IndexX * UnitUV.x, (IndexY + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((IndexX + 1) * UnitUV.x, (IndexY + 1) * UnitUV.y);
}

//=============================================================================
// �\������e�N�X�`���ԍ��ݒ�
//=============================================================================
void SplitTextureDrawer::SetIndex(int Index)
{
	IndexX = Index % DevideX;
	IndexY = Index / DevideX;
	SetTexture();
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void SplitTextureDrawer::Expand_LeftToRight(float Time, EaseType Type)
{
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, Type);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 1.0f, Type);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(IndexX * UnitUV.x, IndexY * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((IndexX + 1) * UnitUV.x, IndexY * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(IndexX * UnitUV.x, (IndexY + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((IndexX + 1) * UnitUV.x, (IndexY + 1) * UnitUV.y);

	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(TexPercent, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(TexPercent, 1.0f);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void SplitTextureDrawer::Expand_RightToLeft(float Time, EaseType Type)
{
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, Type);
	float TexPercent = Easing::EaseValue(Time, 1.0f, 0.0f, Type);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, TextureSize.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(TexPercent, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(TexPercent, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void SplitTextureDrawer::Expand_ToUpDown(float Time, EaseType Type)
{
	float VtxPercent = Easing::EaseValue(Time, 0.0f, 1.0f, Type);
	float TexPercent = Easing::EaseValue(Time, UnitUV.y / 2, 0.0f, Type);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, -TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, TextureSize.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(IndexX * UnitUV.x, IndexY * UnitUV.y + TexPercent);
	Vertex[1].tex = D3DXVECTOR2((IndexX + 1) * UnitUV.x, IndexY * UnitUV.y + TexPercent);
	Vertex[2].tex = D3DXVECTOR2(IndexX * UnitUV.x, (IndexY + 1) * UnitUV.y - TexPercent);
	Vertex[3].tex = D3DXVECTOR2((IndexX + 1) * UnitUV.x, (IndexY + 1) * UnitUV.y - TexPercent);
}

//=============================================================================
// �e�N�X�`���I������
//=============================================================================
void SplitTextureDrawer::Close_UpDown(float Time, EaseType Type)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, Type);
	float TexPercent = Easing::EaseValue(Time, 1.0f, 0.5f, Type);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, -TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, TextureSize.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(0.0f, 1.0f - TexPercent);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 1.0f - TexPercent);
	Vertex[2].tex = D3DXVECTOR2(0.0f, TexPercent);
	Vertex[3].tex = D3DXVECTOR2(1.0f, TexPercent);
}

//=============================================================================
// �e�N�X�`���I������
//=============================================================================
void SplitTextureDrawer::Close_LeftRight(float Time, EaseType Type)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, Type);
	float TexPercent = Easing::EaseValue(Time, 1.0f, 0.5f, Type);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(1.0f - TexPercent, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(TexPercent, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(1.0f - TexPercent, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(TexPercent, 1.0f);
}


//=============================================================================
// �`����W�ݒ菈��
//=============================================================================
void SplitTextureDrawer::SetPosition(D3DXVECTOR3 Pos)
{
	this->Position = Pos;
	SetVertex();
}
