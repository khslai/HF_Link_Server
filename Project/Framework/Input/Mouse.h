//=====================================
//
//�}�E�X�w�b�_[Mouse.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "../../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
namespace Mouse
{
	HRESULT Init(HINSTANCE hInst, HWND hWnd, LPDIRECTINPUT8 pInput);
	void Uninit();
	HRESULT Update();

	 BOOL GetPressLeft(void);      // ���N���b�N�������
	 BOOL GetTriggerLeft(void);    // ���N���b�N�����u��
	 BOOL GetPressRight(void);     // �E�N���b�N�������
	 BOOL GetTriggerRight(void);   // �E�N���b�N�����u��
	 BOOL GetPressCenter(void);    // ���N���b�N�������
	 BOOL GetTriggerCenter(void);  // ���N���b�N�����u��
	 float GetX(void);               // �}�E�X��X�����ɓ��������Βl
	 float GetY(void);               // �}�E�X��Y�����ɓ��������Βl
	 float GetZ(void);               // �}�E�X�z�C�[�������������Βl

	 D3DXVECTOR3 GetMousePosition();
};

#endif