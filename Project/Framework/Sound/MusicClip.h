//=====================================
//
//MusicClip.h
//�@�\:�~���[�W�b�N�f�[�^��Z�߂�N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MUSICCLIP_H_
#define _MUSICCLIP_H_

#include "../../main.h"
#include "../Pattern/BaseState.h"

#include <dsound.h>

/**************************************
MusicClip�N���X
***************************************/
class MusicClip
{
public:
	//�X�e�[�g�񋓎q
	enum State
	{
		Idle,
		Fade,
		OnPlay,
		OnStop,
		OnResume,
		Max
	};

	//�X�e�[�g�N���X�̑O���錾
	class MusicIdle;
	class MusicFade;
	class MusicOnPlay;
	class MusicOnStop;
	class MusicOnResume;

	//�X�e�[�g�N���X�̌^�G�C���A�X
	using MusicState = BaseState<MusicClip, State>;

	//�R���X�g���N�^�A�f�X�g���N�^
	MusicClip(LPDIRECTSOUNDBUFFER8 buffer);
	~MusicClip();

	//�X�V����
	State Update();
	
	//�X�e�[�g�J�ڏ���
	void ChangeState(MusicState* next);

	//�t�F�[�h�p�����[�^�Z�b�g����
	void SetFade(float volume, int duration, bool isFadeOut);

	//�{�����[���Z�b�g����
	void SetVolume(float volume);

private:
	LPDIRECTSOUNDBUFFER8 buffer;		//�T�E���h�o�b�t�@
	float volume;						//���݂̃{�����[��
	float targetVolume;					//�ڕW�{�����[��
	float startVolume;					//�J�n���̃{�����[��
	int cntFrame;						//�t���[���J�E���g
	int fadeDuration;					//�t�F�[�h�ɂ�����t���[��
	bool isPlaying;						//�Đ������ǂ���
	MusicState *state;					//���݂̃X�e�[�g�N���X
	MusicState *prev;					//�ȑO�̃X�e�[�g�N���X
};

/**************************************
MusicIdle�N���X
***************************************/
class MusicClip::MusicIdle : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicFadeIn�N���X
***************************************/
class MusicClip::MusicFade : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicOnPlay�N���X
***************************************/
class MusicClip::MusicOnPlay : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicOnStop�N���X
***************************************/
class MusicClip::MusicOnStop : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};

/**************************************
MusicOnResume�N���X
***************************************/
class MusicClip::MusicOnResume : public MusicClip::MusicState
{
public:
	void OnStart(MusicClip& entity);
	MusicClip::State OnUpdate(MusicClip& entity);
};
#endif