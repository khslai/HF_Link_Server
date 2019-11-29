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
// �R���X�g���N�^(�����Ȃ��e�N�X�`���p)
//=============================================================================
TextureDrawer::TextureDrawer(D3DXVECTOR2 Size, bool Visible) :
	DestScale(1.0f),
	Devide(D3DXVECTOR2(1.0f,1.0f)),
	UnitUV(D3DXVECTOR2(1.0f,1.0f)),
	Index(D3DXVECTOR2(0.0f,0.0f))
{
	this->Size = Size;
	this->Visible = Visible;
	MakeVertex();
}

//=============================================================================
// �R���X�g���N�^(��������e�N�X�`���p)
//=============================================================================
TextureDrawer::TextureDrawer(D3DXVECTOR2 Size, int DevideX, int DevideY, bool Visible) :
	DestScale(1.0f),
	Devide(D3DXVECTOR2((float)DevideX, (float)DevideY)),
	UnitUV(D3DXVECTOR2(1.0f / DevideX, 1.0f / DevideY)),
	Index(D3DXVECTOR2(0.0f, 0.0f))
{
	this->Size = D3DXVECTOR2(Size.x / DevideX, Size.y / DevideY);
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
		!InExpand && !InClose &&
		!InFade)
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
			if (Callback != nullptr)
				Callback();
		}
	}

	// �g��A�k��
	if (InScale)
	{
		Size = Easing::EaseValue(Time, StartSize, StartSize * DestScale, easeType);
		SetVertex();

		if (CountFrame >= Duration)
		{
			StartSize = Size;
			InScale = false;
			if (Callback != nullptr)
				Callback();
		}
	}

	// �t�F�C�h
	if (InFade)
	{
		float Alpha = Easing::EaseValue(Time, StartAlpha, DestAlpha, EaseType::Linear);
		SetAlpha(Alpha);

		if (CountFrame >= Duration)
		{
			StartAlpha = DestAlpha;
			InFade = false;
			if (Callback != nullptr)
				Callback();
		}
	}

	// �W�J
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
		else if (expandType == ExpandType::ToLeftRight)
		{
			Expand_ToLeftRight(Time);
		}

		if (CountFrame >= Duration)
		{
			InExpand = false;
			if (Callback != nullptr)
				Callback();
		}
	}

	// �I��
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
			if (Callback != nullptr)
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
	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);
}

//=============================================================================
// �e�N�X�`��UV�ݒ菈��
//=============================================================================
void TextureDrawer::SetTexture(void)
{
	//Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void TextureDrawer::Expand_LeftToRight(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, UnitUV.x, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * TexPercent, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * TexPercent, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void TextureDrawer::Expand_RightToLeft(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, UnitUV.x, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void TextureDrawer::Expand_ToUpDown(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, 0.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, UnitUV.y / 2, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y + TexPercent);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y - TexPercent);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y - TexPercent);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void TextureDrawer::Expand_ToLeftRight(float Time)
{
	Visible = true;
	float VtxPercent = Easing::EaseValue(Time, 0.0f, 1.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, UnitUV.x / 2, 0.0f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - TexPercent, Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x + TexPercent, (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - TexPercent, (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// �e�N�X�`���I������
//=============================================================================
void TextureDrawer::Close_UpDown(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 0.5f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2, -Size.y / 2 * VtxPercent, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2, Size.y / 2 * VtxPercent, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x, Index.y * UnitUV.y + (UnitUV.y * TexPercent));
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, Index.y * UnitUV.y + (UnitUV.y * TexPercent));
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x, (Index.y + 1) * UnitUV.y - (UnitUV.y * TexPercent));
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x, (Index.y + 1) * UnitUV.y - (UnitUV.y * TexPercent));
}

//=============================================================================
// �e�N�X�`���I������
//=============================================================================
void TextureDrawer::Close_LeftRight(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, 1.0f, 0.0f, easeType);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 0.5f, easeType);

	Vertex[0].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, -Size.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(Size.x / 2 * VtxPercent, Size.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(Index.x * UnitUV.x + (UnitUV.x * TexPercent), Index.y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - (UnitUV.x * TexPercent), Index.y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(Index.x * UnitUV.x + (UnitUV.x * TexPercent), (Index.y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((Index.x + 1) * UnitUV.x - (UnitUV.x * TexPercent), (Index.y + 1) * UnitUV.y);
}

//=============================================================================
// �e�N�X�`���ړ�
//=============================================================================
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

//=============================================================================
// �t�F�C�h����
//=============================================================================
void TextureDrawer::Fade(float Duration, float DestAlpha, std::function<void(void)> callback)
{
	D3DXCOLOR Color = Vertex[0].diffuse;
	InFade = true;
	CountFrame = 0;
	this->Duration = Duration;
	StartAlpha = Color.a;
	this->DestAlpha = DestAlpha;
	Callback = callback;
}

//=============================================================================
// �e�N�X�`���W�J
//=============================================================================
void TextureDrawer::Expand(float Duration, ExpandType expandType, EaseType Type, std::function<void(void)> callback)
{
	InExpand = true;
	Visible = false;
	CountFrame = 0;
	this->Duration = Duration;
	this->expandType = expandType;
	easeType = Type;
	Callback = callback;
}

//=============================================================================
// �e�N�X�`���\���I��
//=============================================================================
void TextureDrawer::Close(float Duration, CloseType closeType, EaseType Type, std::function<void(void)> callback)
{
	InClose = true;
	Visible = true;
	CountFrame = 0;
	this->Duration = Duration;
	this->closeType = closeType;
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
// �`��UV�ݒ�
//=============================================================================
void TextureDrawer::SetIndex(int Index)
{
	this->Index.x = (float)(Index % (int)Devide.x);
	this->Index.y = (float)(Index / (int)Devide.x);
	SetTexture();
}

//=============================================================================
// �`��UV�ݒ�
//=============================================================================
void TextureDrawer::SetIndex(int x, int y)
{
	this->Index.x = (float)x;
	this->Index.y = (float)y;
	SetTexture();
}

//=============================================================================
// �T�C�Y�ݒ�
//=============================================================================
void TextureDrawer::SetScale(float Scale)
{
	Size *= Scale;
}

//=============================================================================
// �e�N�X�`���g��A�k��
//=============================================================================
void TextureDrawer::SetScale(float Duration, float Scale, EaseType Type, std::function<void(void)> callback)
{
	InScale = true;
	CountFrame = 0;
	this->Duration = Duration;
	StartSize = Size;
	DestScale = Scale;
	easeType = Type;
	Callback = callback;
}