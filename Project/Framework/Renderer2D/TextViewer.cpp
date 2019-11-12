//=====================================
//
//TextViewer.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TextViewer.h"

/**************************************
�R���X�g���N�^
***************************************/
TextViewer::TextViewer(const char * fontName, int fontSize) :
	font(NULL),
	fontSize(fontSize),
	posX(10),
	posY(10),
	color(0xffffffff),
	text("text")
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateFont(pDevice, fontSize, 0, 0, D3DX_DEFAULT, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T(fontName), &font);
}

/**************************************
�f�X�g���N�^
***************************************/
TextViewer::~TextViewer()
{
	SAFE_RELEASE(font);
}

/**************************************
�`�揈��
***************************************/
void TextViewer::Draw()
{
	//�e�L�X�g�𒆉��񂹂ŕ\�����邽�߂�Rect���v�Z
	LONG left = posX - text.length() * fontSize / 2;
	//LONG top =  posY - fontSize / 2;
	LONG top =  posY - fontSize;
	LONG right = left + text.length() * fontSize;
	//LONG bottom = top + fontSize;
	LONG bottom = top + fontSize * 2;

	//�`��
	RECT rect = { left, top, right, bottom};
	font->DrawText(NULL, text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER, color);
}

/**************************************
���W�Z�b�g����
***************************************/
void TextViewer::SetPos(int x, int y)
{
	posX = x;
	posY = y;
}

/**************************************
���W�Z�b�g����
***************************************/
void TextViewer::SetColor(const D3DXCOLOR & color)
{
	this->color = color;
}

/**************************************
�e�L�X�g�Z�b�g����
***************************************/
void TextViewer::SetText(const std::string & message)
{
	text = message;
}

/**************************************
�t�H���g���[�h����
***************************************/
void TextViewer::LoadFont(const char * fontFileName)
{
	AddFontResource(fontFileName);
}

/**************************************
�t�H���g�����[�u����
***************************************/
void TextViewer::RemoveFont(const char * fontFileName)
{
	RemoveFontResource(fontFileName);
}
