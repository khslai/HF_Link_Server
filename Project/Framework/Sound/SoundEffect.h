//=====================================
//
//SoundEffect.h
//�@�\:�T�E���h�G�t�F�N�g�Ǘ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

#include "../../main.h"
#include <dsound.h>
#include <unordered_map>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SE
{
public:
	//�T�E���h�ǂݍ��ݏ���
	static void Load(const char* path, int tag);

	//�ǂݍ��񂾃T�E���h���N���A���鏈��
	static void Clear();

	//�Đ�����
	//�{�����[����1.0f ~ 0.0f
	static void Play(int tag, float volume = 1.0f);

	//��~����
	static void Stop(int tag);
	static void Stop();

	//�ĊJ����
	static void Resume(int tag);
	static void Resume();

	//�Đ�������
	static bool IsPlaying(int tag);

private:
	//�ǂݍ��񂾃T�E���h�̃R���e�i
	static std::unordered_map<int, LPDIRECTSOUNDBUFFER8> soundContainer;
};
#endif