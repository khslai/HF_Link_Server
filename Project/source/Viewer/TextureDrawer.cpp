//=============================================================================
//
// �e�N�X�`���`��N���X [TextureDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include"../../main.h"
#include "TextureDrawer.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Math/Easing.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
TextureDrawer::TextureDrawer(D3DXVECTOR2 TextureSize) :
	DevideX(1),
	DevideY(1),
	TextureSize(TextureSize),
	UnitUV(D3DXVECTOR2(1.0f,1.0f))
{
	MakeVertex();
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
TextureDrawer::TextureDrawer(int DevideX, int DevideY, D3DXVECTOR2 TextureSize) :
	DevideX(DevideX),
	DevideY(DevideY)
{
	UnitUV.x = 1.0f / DevideX;
	UnitUV.y = 1.0f / DevideY;
	this->TextureSize.x = TextureSize.x / DevideX;
	this->TextureSize.y = TextureSize.y / DevideY;
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
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void TextureDrawer::LoadTexture(const char *path)
{
	ResourceManager::Instance()->GetTexture(path, Texture);
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void TextureDrawer::LoadTexture(LPDIRECT3DTEXTURE9 *Texture)
{
	if (this->Texture != nullptr)
	{
		SAFE_RELEASE(this->Texture);
	}
	this->Texture = *Texture;
}

//=============================================================================
// �I�u�W�F�N�g�`�揈��
//=============================================================================
void TextureDrawer::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, Texture);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
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
	SetTexture(0);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void TextureDrawer::SetVertex(void)
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
void TextureDrawer::SetTexture(void)
{
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// �e�N�X�`��UV�ݒ菈��
//=============================================================================
void TextureDrawer::SetTexture(int UnitNo)
{
	int x = UnitNo % DevideX;
	int y = UnitNo / DevideX;

	Vertex[0].tex = D3DXVECTOR2(x * UnitUV.x, y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((x + 1) * UnitUV.x, y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(x * UnitUV.x, (y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((x + 1) * UnitUV.x, (y + 1) * UnitUV.y);
}

//=============================================================================
// �e�N�X�`���W�J���o����
//=============================================================================
void TextureDrawer::SetTextureExpand(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, EaseType::InQuart);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 1.0f, EaseType::InQuart);

	// ���_���W�̐ݒ�
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
// �e�N�X�`���̃A���t�@�l�ݒ菈���i���߁j
//=============================================================================
void TextureDrawer::SetAlpha(float alpha)
{
	D3DXCOLOR Color = Vertex[0].diffuse;
	Color.a = alpha;

	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//=============================================================================
// �e�N�X�`���̐F�ݒ菈��
//=============================================================================
void TextureDrawer::SetColor(D3DXCOLOR Color)
{
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//=============================================================================
// �`����W�ݒ菈��
//=============================================================================
void TextureDrawer::SetPosition(D3DXVECTOR3 Pos)
{
	this->Position = Pos;
	SetVertex();
}
