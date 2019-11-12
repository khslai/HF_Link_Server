//=====================================
//
//�Q�[���p�b�h�w�b�_[Gamepad.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "../../main.h"

/**************************************
�}�N����`
***************************************/
#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g
#define PADBUTTON_MAX	14			// ���͂Ɏg����{�^���̍ő吔

#define POV_UP			(0x0001)			//�n�b�g�X�C�b�`�̏�
#define POV_RIGHTUP		(0x0002)			//�n�b�g�X�C�b�`�̉E��
#define POV_RIGHT		(0x0004)			//�n�b�g�X�C�b�`�̉E
#define POV_RIGHTDOWN	(0x0008)			//�n�b�g�X�C�b�`�̉E��
#define POV_DOWN		(0x0010)			//�n�b�g�X�C�b�`�̉�
#define POV_LEFTDOWN	(0x0020)			//�n�b�g�X�C�b�`�̍���
#define POV_LEFT		(0x0040)			//�n�b�g�X�C�b�`�̍�
#define POV_LEFTUP		(0x0080)			//�n�b�g�X�C�b�`�̍���
#define POV_MAX			(8)

/**************************************
�N���X��`
***************************************/
namespace GamePad
{
	HRESULT Init(LPDIRECTINPUT8 pInput);
	void Uninit();
	void Update();

	BOOL GetPress(int padNo, DWORD button);
	BOOL GetRepeat(int padNo, DWORD button);
	BOOL GetTrigger(int padNo, DWORD button);
	BOOL GetRelease(int padNo, DWORD button);

	BOOL GetPressPOV(int padNo, DWORD button);
	BOOL GetRepeatPOV(int padNo, DWORD button);
	BOOL GetTriggerPOV(int padNo, DWORD button);
	BOOL GetReleasePOV(int padNo, DWORD button);

	BOOL GetPressLeft(int padNo);
	BOOL GetPressRight(int padNo);
	BOOL GetRepeatLeft(int padNo);
	BOOL GetRepeatRight(int padNo);
	BOOL GetTriggerLeft(int padNo);
	BOOL GetTriggerRight(int padNo);

	BOOL GetPressDown(int padNo);
	BOOL GetPressUp(int padNo);
	BOOL GetRepeatDown(int padNo);
	BOOL GetRepeatUp(int padNo);
	BOOL GetTriggerDown(int padNo);
	BOOL GetTriggerUp(int padNo);

	float GetRightStickX(int padNo);
	float GetRightStickY(int padNo);

	int GetTriggerX(int padNo);
	int GetTriggerY(int padNo);

	int GetPadCount();

	int GetButtonID(DWORD button);
};

#endif