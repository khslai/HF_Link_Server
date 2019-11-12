/*************************************/
/*!
	@file BaseGame.h
	@brief �Q�[���̃R�A����
	@author GP12B332 21 ���ԗY��
	@addtogroup Core_BaseGame
	@ingroup Core_BaseGame
****************************************/
#ifndef _BASEGAME_H_
#define _BASEGAME_H_

#include "../../main.h"
#include "SceneManager.h"

class Camera;

/********************************************/
/*!
@brief �Q�[���̃R�A�ƂȂ镔���̃N���X
@details ���ۂ̐���ł͂��̃N���X���p�����ăQ�[�����C�������
*********************************************/
class BaseGame
{
public:
	/**	�R���X�g���N�^ */
	BaseGame(HINSTANCE hInstance, HWND hWnd);

	/** �f�X�g���N�^ */
	virtual ~BaseGame();

	/** �X�V���� */
	virtual void Update();

	/** �`�揈�� */
	virtual void Draw();

protected:
	/** �V�[���}�l�[�W�� */
	SceneManager* sceneManager;

	LPDIRECT3DTEXTURE9 renderTexture;	/*!< �`��̈�ƂȂ�e�N�X�`�� */
	LPDIRECT3DSURFACE9 renderSurface;	/*!< �`��̈�ƂȂ�T�[�t�F�C�X */
	LPDIRECT3DVERTEXBUFFER9 screenVtx;	/*!< �`��p���_�o�b�t�@ */

	/** �`��p���_�o�b�t�@�쐬���� */
	virtual void MakeScreen();

	/** �`��̈�쐬���� */
	virtual void MakeRenderTarget();
};


#endif