//=====================================
//
//�L�[�{�[�h�w�b�_[Keyboard.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "../../main.h"

/**************************************
�}�N����`
***************************************/
#define	NUM_KEY_MAX		(256)			// �L�[�ő吔

/**************************************
�N���X��`
***************************************/
namespace Keyboard
{
	HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pInput);
	void Uninit();
	void Update();

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRepeat(int nKey);
	bool GetRelease(int nKey);
};

#endif	