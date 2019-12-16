//=====================================
//
//BackGroundMusic.cpp
//�@�\:BGM�Ǘ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BackGroundMusic.h"
#include "sound.h"

/**************************************
static�����o
***************************************/
std::unordered_map<int, MusicClip*> BGM::musicContainer;
std::vector<MusicClip::MusicState*> BGM::fsm;

/**************************************
static�����o
***************************************/
void BGM::Init()
{
	//�~���[�W�b�N�N���b�v�̃X�e�[�g�}�V���쐬
	fsm.resize(MusicClip::State::Max, NULL);
	fsm[MusicClip::Idle] = new MusicClip::MusicIdle();
	fsm[MusicClip::Fade] = new MusicClip::MusicFade();
	fsm[MusicClip::OnPlay] = new MusicClip::MusicOnPlay();
	fsm[MusicClip::OnStop] = new MusicClip::MusicOnStop();
	fsm[MusicClip::OnResume] = new MusicClip::MusicOnResume();
}

/**************************************
static�����o
***************************************/
void BGM::Uninit()
{
	//�X�e�[�g�}�V���폜
	for (auto&& state : fsm)
	{
		SAFE_DELETE(state);
	}
	fsm.clear();

	Clear();
}

/**************************************
�X�V����
***************************************/
void BGM::Update()
{
	for (auto&& pair : musicContainer)
	{
		MusicClip::State next = pair.second->Update();
		pair.second->ChangeState(fsm[next]);
	}
}

/**************************************
�ǂݍ��ݏ���
***************************************/
void BGM::Load(const char * path, int tag)
{
	//�d���m�F
	if (musicContainer.count(tag) != 0)
		return;

	//�ǂݍ���œo�^
	LPDIRECTSOUNDBUFFER8 buffer = Sound::Load(path);
	MusicClip *music = new MusicClip(buffer);
	musicContainer.emplace(tag, music);

	music->ChangeState(fsm[MusicClip::Idle]);
}

/**************************************
�N���A����
***************************************/
void BGM::Clear()
{
	//�~���[�W�b�N�R���e�i�폜
	for (auto&& pair : musicContainer)
	{
		SAFE_DELETE(pair.second);
	}
	musicContainer.clear();
}

/**************************************
�Đ�����
***************************************/
void BGM::Play(int tag, float volume)
{
	//�o�^�m�F
	if (musicContainer.count(tag) == 0)
		return;

	MusicClip* music = musicContainer[tag];
	music->SetVolume(volume);
	music->ChangeState(fsm[MusicClip::OnPlay]);
}

/**************************************
��~����
***************************************/
void BGM::Stop(int tag)
{
	//�o�^�m�F
	if (musicContainer.count(tag) == 0)
		return;

	musicContainer[tag]->ChangeState(fsm[MusicClip::OnStop]);
}

/**************************************
��~����
***************************************/
void BGM::Stop()
{
	for (auto&& pair : musicContainer)
	{
		Stop(pair.first);
	}
}

/**************************************
�ĊJ����
***************************************/
void BGM::Resume(int tag)
{
	//�o�^�m�F
	if (musicContainer.count(tag) == 0)
		return;

	musicContainer[tag]->ChangeState(fsm[MusicClip::OnResume]);
}

/**************************************
�ĊJ����
***************************************/
void BGM::Resume()
{
	for (auto&& pair : musicContainer)
	{
		Resume(pair.first);			
	}
}

/**************************************
�t�F�[�h�C������
***************************************/
void BGM::FadeIn(int tag, float volume, int duration)
{
	Play(tag, 0.0f);
	Fade(tag, volume, duration, false);
}

/**************************************
�t�F�[�h����
***************************************/
void BGM::Fade(int tag, float volume, int duration, bool flgStop)
{
	//�o�^�m�F
	if (musicContainer.count(tag) == 0)
		return;

	MusicClip *music = musicContainer[tag];
	music->SetFade(volume, duration, flgStop);
	musicContainer[tag]->ChangeState(fsm[MusicClip::Fade]);
}

/**************************************
�t�F�[�h����
***************************************/
void BGM::Fade(float volume, int duration, bool flgStop)
{
	for (auto&& pair : musicContainer)
	{
		Fade(pair.first, volume, duration, flgStop);
	}
}
