//=====================================
//
//BackgroundMusic.h
//�@�\:BGM�Ǘ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BACKGROUNDMUSIC_H_
#define _BACKGROUNDMUSIC_H_

#include "../../main.h"
#include "MusicClip.h"

#include <unordered_map>
#include <vector>
#include <dsound.h>

/**************************************
�O���錾
***************************************/

/**************************************
BGM�N���X
***************************************/
class BGM
{
public:
	static void Init();
	static void Uninit();
	static void Update();

	//�T�E���h�ǂݍ��ݏ���
	static void Load(const char* path, int tag);

	//�ǂݍ��񂾃T�E���h���N���A���鏈��
	static void Clear();

	//�Đ�����
	//�{�����[����1.0f ~ 0.0f
	static void Play(int tag, float volume);

	//��~����
	static void Stop(int tag);
	static void Stop();

	//�ĊJ����
	static void Resume(int tag);
	static void Resume();

	//�t�F�[�h�C���A�t�F�[�h�A�E�g
	static void FadeIn(int tag, float volume, int duration);
	static void Fade(int tag, float volume, int duration, bool flgStop);
	static void Fade(float volume, int duration, bool flgStop);

private:
	//�ǂݍ��񂾃T�E���h�̃R���e�i
	static std::unordered_map<int, MusicClip*> musicContainer;

	//MusicClip�̃X�e�[�g�}�V��
	static std::vector<MusicClip::MusicState*> fsm;
};

#endif