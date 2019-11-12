//=====================================
//
//�Q�[���p�b�h����[Gamepad.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Gamepad.h"
#include "../Tool/DebugWindow.h"

namespace GamePad
{
	/**************************************
	�}�N����`
	***************************************/
	#define DEADZONE		5000			// �e����25%�𖳌��]�[���Ƃ���
	#define RANGE_MAX		1000			// �L���͈͂̍ő�l
	#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l

	#define INPUT_SHORTWAIT (6)

	/**************************************
	�O���[�o���ϐ�
	***************************************/
	static LPDIRECTINPUT8 pInput = NULL;
	static LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// �p�b�h�f�o�C�X
	static int		padCount;			// ���o�����p�b�h�̐�

	//�X�e�B�b�N��Repeat��Ԍ��o�p
	static int		padAxisXRepeat[GAMEPADMAX];
	static int		padAxisYRepeat[GAMEPADMAX];
	static int		lastAxisX[GAMEPADMAX];
	static int		lastAxisY[GAMEPADMAX];
	static int		axisXRepeatCnt[GAMEPADMAX];
	static int		axisYRepeatCnt[GAMEPADMAX];

	static float	padAxislRx[GAMEPADMAX];
	static float	padAxislRy[GAMEPADMAX];

	static DWORD	padState[GAMEPADMAX];	// �p�b�h���i�����Ή��j
	static DWORD	padTrigger[GAMEPADMAX];
	static DWORD	padRelease[GAMEPADMAX];
	static DWORD	padRepeat[GAMEPADMAX];
	static int		padRepeatCnt[GAMEPADMAX][PADBUTTON_MAX];

	static DWORD	povState[GAMEPADMAX];
	static DWORD	povTrigger[GAMEPADMAX];
	static DWORD	povRelease[GAMEPADMAX];
	static DWORD	povRepeat[GAMEPADMAX];
	static int	povRepeatCnt[GAMEPADMAX][POV_MAX];

	/**************************************
	�p�b�h�����R�[���o�b�N
	***************************************/
	BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
	{
		HRESULT result;

		result = pInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
		return DIENUM_CONTINUE;	// ���̃f�o�C�X���
	}

	/**************************************
	����������
	***************************************/
	HRESULT Init(LPDIRECTINPUT8 inputInterface)			// �p�b�h������
	{
		HRESULT		result;
		int			i;

		padCount = 0;

		for (i = 0; i < GAMEPADMAX; i++)
		{
			padState[i] = 0x00000000l;	// ������
			padTrigger[i] = 0x00000000l;	// ������
			padRelease[i] = 0x00000000l;	// ������
		}

		// �W���C�p�b�h��T��
		pInput = inputInterface;
		inputInterface->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchPadCallback, NULL, DIEDFL_ATTACHEDONLY);
		// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B

		for (i = 0; i < padCount; i++) {
			// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
			result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
			if (FAILED(result))
				return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

		  // ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		  //		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		  //		if ( FAILED(result) )
		  //			return false; // ���[�h�̐ݒ�Ɏ��s

		  // ���̒l�͈̔͂�ݒ�
		  // X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
		  // (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
		  // ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
			DIPROPRANGE				diprg;
			ZeroMemory(&diprg, sizeof(diprg));
			diprg.diph.dwSize = sizeof(diprg);
			diprg.diph.dwHeaderSize = sizeof(diprg.diph);
			diprg.diph.dwHow = DIPH_BYOFFSET;
			diprg.lMin = RANGE_MIN;
			diprg.lMax = RANGE_MAX;
			// X���͈̔͂�ݒ�
			diprg.diph.dwObj = DIJOFS_X;
			pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
			// Y���͈̔͂�ݒ�
			diprg.diph.dwObj = DIJOFS_Y;
			pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

			// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
			// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
			// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
			DIPROPDWORD				dipdw;
			dipdw.diph.dwSize = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
			dipdw.diph.dwHow = DIPH_BYOFFSET;
			dipdw.dwData = DEADZONE;
			//X���̖����]�[����ݒ�
			dipdw.diph.dwObj = DIJOFS_X;
			pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
			//Y���̖����]�[����ݒ�
			dipdw.diph.dwObj = DIJOFS_Y;
			pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

			//�W���C�X�e�B�b�N���͐���J�n
			pGamePad[i]->Acquire();
		}

		return true;

	}

	/**************************************
	�I������
	***************************************/
	void Uninit()
	{
		for (int i = 0; i < GAMEPADMAX; i++) {
			if (pGamePad[i])
			{
				pGamePad[i]->Unacquire();
				pGamePad[i]->Release();
			}
		}
	}

	/**************************************
	�X�V����
	***************************************/
	void Update(void)
	{
		HRESULT			result;
		DIJOYSTATE2		dijs;
		int				i;

		for (i = 0; i < padCount; i++)
		{
			DWORD lastPadState;
			lastPadState = padState[i];
			padState[i] = 0x00000000l;	// ������

			result = pGamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
			if (FAILED(result)) {
				result = pGamePad[i]->Acquire();
				while (result == DIERR_INPUTLOST)
					result = pGamePad[i]->Acquire();
			}

			result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
				result = pGamePad[i]->Acquire();
				while (result == DIERR_INPUTLOST)
					result = pGamePad[i]->Acquire();
			}

			if (dijs.lZ != 0 && dijs.lRx != 0)
			{
				padAxislRx[i] = (float)(dijs.lRx);
				padAxislRy[i] = (float)(dijs.lRy);

			}
			else
			{
				padAxislRx[i] = (float)(dijs.lZ + dijs.lRx);
				padAxislRy[i] = (float)(dijs.lRz + dijs.lRy);

			}

			// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
			//* y-axis (forward)
			if (dijs.lY < 0)
				padState[i] |= BUTTON_UP;
			//* y-axis (backward)
			if (dijs.lY > 0)
				padState[i] |= BUTTON_DOWN;
			//* x-axis (left)
			if (dijs.lX < 0)
				padState[i] |= BUTTON_LEFT;
			//* x-axis (right)
			if (dijs.lX > 0)
				padState[i] |= BUTTON_RIGHT;
			//* �`�{�^��
			if (dijs.rgbButtons[0] & 0x80)
				padState[i] |= BUTTON_A;
			//* �a�{�^��
			if (dijs.rgbButtons[1] & 0x80)
				padState[i] |= BUTTON_B;
			//* �b�{�^��
			if (dijs.rgbButtons[2] & 0x80)
				padState[i] |= BUTTON_C;
			//* �w�{�^��
			if (dijs.rgbButtons[3] & 0x80)
				padState[i] |= BUTTON_X;
			//* �x�{�^��
			if (dijs.rgbButtons[4] & 0x80)
				padState[i] |= BUTTON_Y;
			//* �y�{�^��
			if (dijs.rgbButtons[5] & 0x80)
				padState[i] |= BUTTON_Z;
			//* �k�{�^��
			if (dijs.rgbButtons[6] & 0x80)
				padState[i] |= BUTTON_L;
			//* �q�{�^��
			if (dijs.rgbButtons[7] & 0x80)
				padState[i] |= BUTTON_R;
			//* �r�s�`�q�s�{�^��
			if (dijs.rgbButtons[8] & 0x80)
				padState[i] |= BUTTON_START;
			//* �l�{�^��
			if (dijs.rgbButtons[9] & 0x80)
				padState[i] |= BUTTON_M;

			// Trigger�ݒ�
			padTrigger[i] = ((lastPadState ^ padState[i])	// �O��ƈ���Ă���
				& padState[i]);					// ��������ON�̂��

												// Release�ݒ�
			padRelease[i] = ((lastPadState ^ padState[i]))	//�O��ƈ���Ă���
				& (~padState[i]);				//��OFF�̂��

			// Repeat�ݒ�
			memcpy(&padRepeat[i], &padTrigger[i], sizeof(DWORD));
			for (DWORD button = BUTTON_UP; button <= BUTTON_M; button = button << 1)
			{
				int buttonID = GetButtonID(button);
				if (GetPress(i, button))
				{
					padRepeatCnt[i][buttonID]++;

					if (padRepeatCnt[i][buttonID] >= 20 && padRepeatCnt[i][buttonID] % 5 == 0)
					{
						padRepeat[i] |= button;
					}
				}
				else
				{
					padRepeat[i] &= ~button;
					padRepeatCnt[i][buttonID] = 0;
				}
			}

			//POV�ݒ�
			DWORD lastPovState = povState[i];
			ZeroMemory(&povState[i], sizeof(DWORD));

			//����
			if (dijs.rgdwPOV[0] != -1)
			{
				povState[i] = 1 << (dijs.rgdwPOV[0] / 4500);
			}

			//Trigger & Release�ݒ�
			povTrigger[i] = ((lastPovState ^ povState[i]) & povState[i]);
			povRelease[i] = ((lastPovState ^ povState[i]) & (~povState[i]));

			//Repeat�ݒ�
			memcpy(&povRepeat[i], &povTrigger[i], sizeof(DWORD));
			for (DWORD pov = POV_UP; pov <= POV_LEFTUP; pov = pov << 1)
			{
				int povID = GetButtonID(pov);
				if (GetPressPOV(i, pov))
				{
					povRepeatCnt[i][povID]++;

					if (povRepeatCnt[i][povID] >= 20 && povRepeatCnt[i][povID] % 5 == 0)
					{
						povRepeat[i] |= pov;
					}
				}
				else
				{
					povRepeat[i] &= ~pov;
					povRepeatCnt[i][povID] = 0;
				}
			}
		}

	}

	/**************************************
	�v���X���o����
	***************************************/
	BOOL GetPress(int padNo, DWORD button)
	{
		return (button & padState[padNo]);
	}

	/**************************************
	���s�[�g���o����
	***************************************/
	BOOL GetRepeat(int padNo, DWORD button)
	{
		return (button & padRepeat[padNo]);
	}

	/**************************************
	�g���K�[���o����
	***************************************/
	BOOL GetTrigger(int padNo, DWORD button)
	{
		return (button & padTrigger[padNo]);
	}

	/**************************************
	�����[�X���o����
	***************************************/
	BOOL GetRelease(int padNo, DWORD button)
	{
		return (button & padRelease[padNo]);
	}

	/**************************************
	�n�b�g�X�C�b�`�v���X���o����
	***************************************/
	BOOL GetPressPOV(int padNo, DWORD button)
	{
		return (button & povState[padNo]);
	}

	/**************************************
	�n�b�g�X�C�b�`���s�[�g���o����
	***************************************/
	BOOL GetRepeatPOV(int padNo, DWORD button)
	{
		return (button & povRepeat[padNo]);
	}

	/**************************************
	�n�b�g�X�C�b�`�g���K�[���o����
	***************************************/
	BOOL GetTriggerPOV(int padNo, DWORD button)
	{
		return (button & povTrigger[padNo]);
	}

	/**************************************
	�n�b�g�X�C�b�`�����[�X���o����
	***************************************/
	BOOL GetReleasePOV(int padNo, DWORD button)
	{
		return (button & povRelease[padNo]);
	}

	/**************************************
	�E�v���X���o����
	***************************************/
	BOOL GetPressLeft(int padNo)
	{
		return GetPress(padNo, BUTTON_LEFT) || GetPressPOV(padNo, POV_LEFT) || GetPressPOV(padNo, POV_LEFTUP) || GetPressPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	�E�v���X���o����
	***************************************/
	BOOL GetPressRight(int padNo)
	{
		return GetPress(padNo, BUTTON_RIGHT) || GetPressPOV(padNo, POV_RIGHT) || GetPressPOV(padNo, POV_RIGHTUP) || GetPressPOV(padNo, POV_RIGHTDOWN);
	}

	/**************************************
	�����s�[�g���o����
	***************************************/
	BOOL GetRepeatLeft(int padNo)
	{
		return GetRepeat(padNo, BUTTON_LEFT) || GetRepeatPOV(padNo, POV_LEFT) || GetRepeatPOV(padNo, POV_LEFTUP) || GetRepeatPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	�E���s�[�g���o����
	***************************************/
	BOOL GetRepeatRight(int padNo)
	{
		return GetRepeat(padNo, BUTTON_RIGHT) || GetRepeatPOV(padNo, POV_RIGHT) || GetRepeatPOV(padNo, POV_RIGHTUP) || GetRepeatPOV(padNo, POV_RIGHTDOWN);
	}

	/**************************************
	���g���K�[���o����
	***************************************/
	BOOL GetTriggerLeft(int padNo)
	{
		return GetTrigger(padNo, BUTTON_LEFT) || GetTriggerPOV(padNo, POV_LEFT) || GetTriggerPOV(padNo, POV_LEFTUP) || GetTriggerPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	�E�g���K�[���o����
	***************************************/
	BOOL GetTriggerRight(int padNo)
	{
		return GetTrigger(padNo, BUTTON_RIGHT) || GetTriggerPOV(padNo, POV_RIGHT) || GetTriggerPOV(padNo, POV_RIGHTUP) || GetTriggerPOV(padNo, POV_RIGHTDOWN);
	}

	/**************************************
	���v���X���o����
	***************************************/
	BOOL GetPressDown(int padNo)
	{
		return GetPress(padNo, BUTTON_DOWN) || GetPressPOV(padNo, POV_DOWN) || GetPressPOV(padNo, POV_RIGHTDOWN) || GetPressPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	��v���X���o����
	***************************************/
	BOOL GetPressUp(int padNo)
	{
		return GetPress(padNo, BUTTON_UP) || GetPressPOV(padNo, POV_UP) || GetPressPOV(padNo, POV_RIGHTUP) || GetPressPOV(padNo, POV_LEFTUP);
	}

	/**************************************
	�����s�[�g���o����
	***************************************/
	BOOL GetRepeatDown(int padNo)
	{
		return GetRepeat(padNo, BUTTON_DOWN) || GetRepeatPOV(padNo, POV_DOWN) || GetRepeatPOV(padNo, POV_RIGHTDOWN) || GetRepeatPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	�ナ�s�[�g���o����
	***************************************/
	BOOL GetRepeatUp(int padNo)
	{
		return GetRepeat(padNo, BUTTON_UP) || GetRepeatPOV(padNo, POV_UP) || GetRepeatPOV(padNo, POV_RIGHTUP) || GetRepeatPOV(padNo, POV_LEFTUP);
	}

	/**************************************
	���g���K�[���o����
	***************************************/
	BOOL GetTriggerDown(int padNo)
	{
		return GetTrigger(padNo, BUTTON_DOWN) || GetTriggerPOV(padNo, POV_DOWN) || GetTriggerPOV(padNo, POV_RIGHTDOWN) || GetTriggerPOV(padNo, POV_LEFTDOWN);
	}

	/**************************************
	��g���K�[���o����
	***************************************/
	BOOL GetTriggerUp(int padNo)
	{
		return GetTrigger(padNo, BUTTON_UP) || GetTriggerPOV(padNo, POV_UP) || GetTriggerPOV(padNo, POV_RIGHTUP) || GetTriggerPOV(padNo, POV_LEFTUP);
	}

	/**************************************
	X���g���K�[���o����
	***************************************/
	int GetTriggerX(int padNo)
	{
		if (GetTrigger(padNo, BUTTON_RIGHT))
			return 1;

		else if (GetTrigger(padNo, BUTTON_LEFT))
			return -1;

		else
			return 0;
	}

	/**************************************
	Y���g���K�[���o����
	***************************************/
	int GetTriggerY(int padNo)
	{
		if (GetTrigger(padNo, BUTTON_UP))
			return 1;

		else if (GetTrigger(padNo, BUTTON_DOWN))
			return -1;

		else
			return 0;
	}

	/**************************************
	�p�b�h����Ԃ�����
	***************************************/
	int GetPadCount(void)
	{
		return padCount;
	}

	/**************************************
	�{�^��ID�擾����
	***************************************/
	int GetButtonID(DWORD button)
	{
		int id = 0;
		for (DWORD bit = button; bit > 0x01; bit = bit >> 1)
		{
			id++;
		}

		return id;
	}

	/**************************************
	�E�X�e�B�b�NX�����͌v�Z����
	***************************************/
	float GetRightStickX(int padNo)
	{
		if (padNo >= padCount)
		{
			return 0.0f;
		}

		return (padAxislRx[padNo] / 65535.0f) - 0.5f;
	}

	/**************************************
	�E�X�e�B�b�NY�����͌v�Z����
	***************************************/
	float GetRightStickY(int padNo)
	{
		if (padNo >= padCount)
		{
			return 0.0f;
		}


		return (padAxislRy[padNo] / 65535.0f) - 0.5f;
	}
}

