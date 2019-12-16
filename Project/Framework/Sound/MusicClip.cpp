//=====================================
//
//MusicClip.cpp
//�@�\:�~���[�W�b�N�f�[�^��Z�߂�N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MusicClip.h"
#include "sound.h"
#include "../Math/Easing.h"

/**************************************
�R���X�g���N�^
***************************************/
MusicClip::MusicClip(LPDIRECTSOUNDBUFFER8 buffer) :
	buffer(buffer),
	volume(0.0f),
	targetVolume(0.0f),
	startVolume(0.0f),
	cntFrame(0),
	fadeDuration(0),
	isPlaying(false)
{
}

/**************************************
�f�X�g���N�^
***************************************/
MusicClip::~MusicClip()
{
	SAFE_RELEASE(buffer);
}

/**************************************
�X�V����
***************************************/
MusicClip::State MusicClip::Update()
{
	return state->OnUpdate(*this);
}

/**************************************
�X�e�[�g�J�ڏ���
***************************************/
void MusicClip::ChangeState(MusicState * next)
{
	if (next == state)
		return;

	prev = state;
	state = next;
	state->OnStart(*this);
}

/**************************************
�t�F�[�h�p�����[�^�Z�b�g����
***************************************/
void MusicClip::SetFade(float volume, int duration, bool isFadeOut)
{
	targetVolume = volume;
	fadeDuration = duration;
	isPlaying = !isFadeOut;
}

/**************************************
�{�����[���Z�b�g����
***************************************/
void MusicClip::SetVolume(float volume)
{
	Sound::SetVolume(buffer, volume);
}

/**************************************
�A�C�h���X�e�[�g�J�n����
***************************************/
void MusicClip::MusicIdle::OnStart(MusicClip & entity)
{
	//���ɉ������Ȃ�
}

/**************************************
�A�C�h���X�e�[�g�X�V����
***************************************/
MusicClip::State MusicClip::MusicIdle::OnUpdate(MusicClip & entity)
{
	//���ɉ������Ȃ�
	return MusicClip::Idle;
}

/**************************************
�t�F�[�h�X�e�[�g�J�n����
***************************************/
void MusicClip::MusicFade::OnStart(MusicClip & entity)
{
	//�t���[���J�E���g���Z�b�g
	entity.cntFrame = 0;
	entity.startVolume = entity.volume;

	if (entity.isPlaying)
		Sound::Play(entity.buffer, Sound::E_DS8_FLAG_LOOP, false);
}

/**************************************
�t�F�[�h�X�e�[�g�X�V����
***************************************/
MusicClip::State MusicClip::MusicFade::OnUpdate(MusicClip & entity)
{
	State next = MusicClip::Fade;

	//�t���[�����J�E���g���ă{�����[�������߂�
	entity.cntFrame++;
	float t = (float)entity.cntFrame / entity.fadeDuration;

	entity.volume = Easing::EaseValue(t, entity.startVolume, entity.targetVolume, EaseType::Linear);
	Sound::SetVolume(entity.buffer, entity.volume);

	//�t�F�[�h���Ԃ��I���Ȃ�J��
	if (entity.cntFrame == entity.fadeDuration)
	{
		next = entity.isPlaying ? MusicClip::Idle : MusicClip::OnStop;
	}

	return next;
}

/**************************************
�v���C�X�e�[�g�J�n����
***************************************/
void MusicClip::MusicOnPlay::OnStart(MusicClip & entity)
{
	//�Đ��J�n
	Sound::Play(entity.buffer, Sound::E_DS8_FLAG_LOOP, true);
	entity.isPlaying = true;
}

/**************************************
�v���C�X�e�[�g�X�V����
***************************************/
MusicClip::State MusicClip::MusicOnPlay::OnUpdate(MusicClip & entity)
{
	//�������Ȃ��̂ŃA�C�h���X�e�[�g�֑J��
	return MusicClip::Idle;
}

/**************************************
�X�g�b�v�X�e�[�g�J�n����
***************************************/
void MusicClip::MusicOnStop::OnStart(MusicClip & entity)
{
	//��~����
	Sound::Stop(entity.buffer);
	entity.isPlaying = false;
}

/**************************************
�X�g�b�v�X�e�[�g�X�V����
***************************************/
MusicClip::State MusicClip::MusicOnStop::OnUpdate(MusicClip & entity)
{
	//�Ȃɂ��ɂȂ��̂ŃA�C�h���X�e�[�g�֑J��
	return MusicClip::Idle;
}

/**************************************
�ĊJ�X�e�[�g�J�n����
***************************************/
void MusicClip::MusicOnResume::OnStart(MusicClip & entity)
{
	//�ĊJ����
	Sound::Play(entity.buffer, Sound::E_DS8_FLAG_LOOP, false);
	entity.isPlaying = true;
	entity.state = entity.prev;
	entity.prev = this;
}

/**************************************
�ĊJ�X�e�[�g�X�V����
***************************************/
MusicClip::State MusicClip::MusicOnResume::OnUpdate(MusicClip & entity)
{
	//�Ȃɂ��ɂȂ��̂ŃA�C�h���X�e�[�g�֑J��
	return MusicClip::Idle;
}
