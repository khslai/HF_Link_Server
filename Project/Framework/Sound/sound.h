#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

// �}�N����`
#define SOUND_VOLUME_MAX	(100.0f)		//���ʍő�%
#define SOUND_VOLUME_MIN	(0.0f)			//���ʍŏ�%
#define SOUND_VOLUME_INIT	(50.0f)			//��������

namespace Sound
{
	enum
	{	// �Đ��p�t���O
		E_DS8_FLAG_NONE,
		E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
		E_DS8_FLAG_MAX
	};

	HRESULT					Init(HWND hWnd);	// ������
	void					Uninit();			// ��Еt��
	LPDIRECTSOUNDBUFFER8	Load(const TCHAR *path);	// �T�E���h�̃��[�h
	void					Play(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0, bool fromHead = false);	// �����ƂɍĐ�
	void					Stop(LPDIRECTSOUNDBUFFER8 pBuffer);					// �����~�߂�
	bool					IsPlaying(LPDIRECTSOUNDBUFFER8 pBuffer);					// �Đ������ǂ���
	void					SetVolume(LPDIRECTSOUNDBUFFER8 pBuffer, float volume);	// �T�E���h�̃{�����[���ݒ�֐�
}
#endif