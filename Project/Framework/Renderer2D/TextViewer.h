//=====================================
//
//TextViewer.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TEXTVIEWER_H_
#define _TEXTVIEWER_H_

#include "../../main.h"

#include <string>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TextViewer
{
public:
	//�R���X�g���N�^
	//fontName : �g�p����t�H���g�̖��O
	//size : �\���t�H���g�T�C�Y
	TextViewer(const char* fontName, int size);

	//�f�X�g���N�^
	~TextViewer();

	//�`�揈��
	void Draw();

	//���W�Z�b�g����
	void SetPos(int x, int y);

	//�J���[�Z�b�g����
	void SetColor(const D3DXCOLOR& color);

	//�\���e�L�X�g�Z�b�g����
	void SetText(const std::string& message);
	
	//�t�H���g�ǂݍ��ݏ���
	//���O�̃t�H���g���g�p����ꍇ�Ƀt�H���g���ꎞ�I�ɃC���X�g�[������
	//fontFileName : �C���X�g�[������t�H���g�t�@�C���ւ̃p�X
	static void LoadFont(const char* fontFileName);

	//�t�H���g�A���C���X�g�[������
	//�ꎞ�I�ɃC���X�g�[���������O�̃t�H���g���A���C���X�g�[������
	//fontFileName : �A���C���X�g�[���t�H���g�t�@�C���ւ̃p�X
	static void RemoveFont(const char* fontFileName);

private:
	//�t�H���g�C���^�[�t�F�C�X
	ID3DXFont * font;

	//�t�H���g�T�C�Y
	int fontSize;

	//�\�����W
	int posX;
	int posY;

	//�\���J���[
	D3DXCOLOR color;

	//�\��������
#if _UNICODE
	wstring str;
#else
	std::string text;
#endif
};

#endif