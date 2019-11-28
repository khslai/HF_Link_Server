//=============================================================================
//
// �e�N�X�`���`��N���X [TextureDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include"../../../main.h"
#include "TextureDrawer.h"
#include "../../../Framework/Math/Easing.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
TextureDrawer::TextureDrawer(D3DXVECTOR2 TextureSize, bool Visible) :
	DestScale(1.0f),
	StartSize(TextureSize)
{
	this->TextureSize = TextureSize;
	this->Visible = Visible;
	MakeVertex();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
TextureDrawer::~TextureDrawer()
{
	SAFE_RELEASE(Texture);
}

//=============================================================================
// �X�V����
//=============================================================================
void TextureDrawer::Update()
{
	if (!InMove && !InScale &&
		!InExpand && !InClose)
		return;

	CountFrame++;
	float Time = (float)CountFrame / Duration;

	// �ړ�����
	if (InMove)
	{
		Position = Easing::EaseValue(Time, StartPos, DestPos, easeType);
		SetVertex();

		if (CountFrame >= Duration)
		{
			StartPos = DestPos;
			InMove = false;
			Callback();
		}
	}

	// �g��A�k��
	if (InScale)
	{
		TextureSize = Easing::EaseValue(Time, StartSize, StartSize * DestScale, easeType);
		SetVertex();

		if (CountFrame >= Duration)
		{
			StartSize = TextureSize;
			InScale = false;
			Callback();
		}
	}

	if (InExpand)
	{
		if (expandType == ExpandType::LeftToRight)
		{
			Expand_LeftToRight(Time);
		}
		else if (expandType == ExpandType::RightToLeft)
		{
			Expand_RightToLeft(Time);
		}
		else if (expandType == ExpandType::ToUpDown)
		{
			Expand_ToUpDown(Time);
		}

		if (CountFrame >= Duration)
		{
			InExpand = false;
			Callback();
		}
	}

	if (InClose)
	{
		if (closeType == CloseType::FromUpDown)
		{
			Close_UpDown(Time);
		}
		else if (closeType == CloseType::FromLeftRight)
		{
			Close_LeftRight(Time);
		}

		if (CountFrame >= Duration)
		{
			Visible = false;
			InClose = false;
			Callback();
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void TextureDrawer::MakeVertex()
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
void TextureDrawer::SetVertex()
{
	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, TextureSize.y / 2, 0.0f);
}

//=============================================================================
// �e�N�X�`��UV�ݒ菈��
//=============================================================================
void TextureDrawer::SetTexture(void)
{
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void TextureDrawer::Expand_LeftToRight(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 1.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(TexPercent, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(TexPercent, 1.0f);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void TextureDrawer::Expand_RightToLeft(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 1.0f, 0.0f, easeType);

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
void TextureDrawer::Expand_ToUpDown(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, 0.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.5f, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, -TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, TextureSize.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(0.0f, TexPercent);
	Vertex[1].tex = D3DXVECTOR2(1.0f, TexPercent);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f - TexPercent);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f - TexPercent);
}

//=============================================================================
// �e�N�X�`���I������
//=============================================================================
void TextureDrawer::Close_UpDown(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 1.0f, 0.5f, easeType);

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
void TextureDrawer::Close_LeftRight(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 1.0f, 0.5f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(1.0f - TexPercent, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(TexPercent, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(1.0f - TexPercent, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(TexPercent, 1.0f);
}

void TextureDrawer::Move(float Duration, D3DXVECTOR3 GoalPos, EaseType Type, std::function<void(void)> callback)
{
	InMove = true;
	CountFrame = 0;
	this->Duration = Duration;
	StartPos = Position;
	DestPos = GoalPos;
	easeType = Type;
	Callback = callback;
}

void TextureDrawer::SetScale(float Duration, float Scale, EaseType Type, std::function<void(void)> callback)
{
	InScale = true;
	CountFrame = 0;
	this->Duration = Duration;
	StartSize = TextureSize;
	DestScale = Scale;
	easeType = Type;
	Callback = callback;
}

void TextureDrawer::Expand(float Duration, int expandType, EaseType Type, std::function<void(void)> callback)
{
	InExpand = true;
	Visible = false;
	CountFrame = 0;
	this->Duration = Duration;
	this->expandType = expandType;
	easeType = Type;
	Callback = callback;
}

void TextureDrawer::Close(float Duration, int closeType, EaseType Type, std::function<void(void)> callback)
{
	InClose = true;
	CountFrame = 0;
	this->Duration = Duration;
	this->expandType = closeType;
	easeType = Type;
	Callback = callback;
}

//=============================================================================
// �`����W�ݒ�
//=============================================================================
void TextureDrawer::SetPosition(D3DXVECTOR3 Pos)
{
	Position = Pos;
	SetVertex();
}

//=============================================================================
// �T�C�Y�ݒ�
//=============================================================================
void TextureDrawer::SetScale(float Scale)
{
	TextureSize *= Scale;
}