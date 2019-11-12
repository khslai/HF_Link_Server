//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "input.h"

namespace Input
{
	//*****************************************************************************
	// �O���[�o���ϐ�
	//*****************************************************************************
	LPDIRECTINPUT8 pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^

	//=============================================================================
	// ���͏����̏�����
	//=============================================================================
	HRESULT Init(HINSTANCE hInst, HWND hWnd)
	{
		HRESULT hr;

		if (!pDInput)
		{
			// DirectInput�I�u�W�F�N�g�̍쐬
			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
				IID_IDirectInput8, (void**)&pDInput, NULL);
		}

		// �L�[�{�[�h�̏�����
		Keyboard::Init(hInst, hWnd, pDInput);

		//�}�E�X������
		Mouse::Init(hInst, hWnd, pDInput);

		//�p�b�h����������
		GamePad::Init(pDInput);

		return S_OK;
	}

	//=============================================================================
	// ���͏����̏I������
	//=============================================================================
	void Uninit()
	{
		// �L�[�{�[�h�̏I������
		Keyboard::Uninit();

		//�}�E�X�I������
		Mouse::Uninit();

		//�p�b�h�I������
		GamePad::Uninit();

		if (pDInput)
		{// DirectInput�I�u�W�F�N�g�̊J��
			pDInput->Release();
			pDInput = NULL;
		}
	}

	//=============================================================================
	// ���͏����̍X�V����
	//=============================================================================
	void Update(void)
	{
		// �L�[�{�[�h�̍X�V
		Keyboard::Update();

		//�}�E�X�X�V����
		Mouse::Update();

		//�Q�[���p�b�h�X�V����
		GamePad::Update();
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetPressHorizontail(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_LEFT) || GamePad::GetPressLeft(0))
				return -1.0f;

			if (Keyboard::GetPress(DIK_RIGHT) || GamePad::GetPressRight(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPressLeft(no))
				return -1.0f;

			if (GamePad::GetPressRight(no))
				return 1.0f;

			return 0.0f;
		}
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetPressVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetPress(DIK_DOWN) || GamePad::GetPressDown(0))
				return -1.0f;

			if (Keyboard::GetPress(DIK_UP) || GamePad::GetPressUp(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetPressDown(no))
				return -1.0f;

			if (GamePad::GetPressUp(no))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetTriggerHorizontal(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetTrigger(DIK_LEFT) || GamePad::GetTriggerLeft(0))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_RIGHT) || GamePad::GetTriggerRight(0))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTriggerLeft(no))
				return -1.0f;

			if (GamePad::GetTriggerRight(no))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetTriggerVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetTrigger(DIK_DOWN) || GamePad::GetTriggerDown(0))
				return -1.0f;

			if (Keyboard::GetTrigger(DIK_UP) || GamePad::GetTriggerUp(0))
				return 1.0f;
		}
		else
		{
			if (GamePad::GetTriggerDown(no))
				return -1.0f;

			if (GamePad::GetTriggerUp(no))
				return 1.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetRepeatHorizontal(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_LEFT) || GamePad::GetRepeatLeft(0))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_RIGHT) || GamePad::GetRepeatRight(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeatLeft(no))
				return -1.0f;

			if (GamePad::GetRepeatRight(no))
				return 1.0f;

			return 0.0f;
		}

		return 0.0f;
	}

	//=============================================================================
	// ���������ւ̓��͏���
	//=============================================================================
	float GetRepeatVertical(int no)
	{
		if (no == 0)
		{
			if (Keyboard::GetRepeat(DIK_DOWN) || GamePad::GetRepeatDown(0))
				return -1.0f;

			if (Keyboard::GetRepeat(DIK_UP) || GamePad::GetRepeatUp(0))
				return 1.0f;

			return 0.0f;
		}
		else
		{
			if (GamePad::GetRepeatDown(no))
				return -1.0f;

			if (GamePad::GetRepeatUp(no))
				return 1.0f;
		}

		return 0.0f;
	}
}