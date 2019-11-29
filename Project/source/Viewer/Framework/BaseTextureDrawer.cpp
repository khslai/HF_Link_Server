//=============================================================================
//
// �e�N�X�`���`����N���X [BaseTextureDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include"../../../main.h"
#include "BaseTextureDrawer.h"
#include "../../../Framework/Resource/ResourceManager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
BaseTextureDrawer::BaseTextureDrawer()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
BaseTextureDrawer::~BaseTextureDrawer()
{
	SAFE_RELEASE(Texture);
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void BaseTextureDrawer::LoadTexture(const char *path)
{
	ResourceManager::Instance()->GetTexture(path, Texture);
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
void BaseTextureDrawer::LoadTexture(LPDIRECT3DTEXTURE9 *Texture)
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
void BaseTextureDrawer::Draw()
{
	// �����t���O�A�W�J�������K�v
	if (!Visible)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, Texture);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}

//=============================================================================
// �e�N�X�`���̃T�C�Y�ݒ�
//=============================================================================
void BaseTextureDrawer::SetSize(D3DXVECTOR2 Size)
{
	this->Size = Size;
}

//=============================================================================
// �e�N�X�`���̃A���t�@�l�ݒ菈���i���߁j
//=============================================================================
void BaseTextureDrawer::SetAlpha(float alpha)
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
void BaseTextureDrawer::SetColor(D3DXCOLOR Color)
{
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}