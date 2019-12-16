//=====================================
//
//SoundEffect.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SoundEffect.h"
#include "sound.h"
#include "../Tool/DebugWindow.h"

/**************************************
static�����o
***************************************/
std::unordered_map<int, LPDIRECTSOUNDBUFFER8> SE::soundContainer;

/**************************************
�ǂݍ��ݏ���
***************************************/
void SE::Load(const char * path, int tag)
{
	//�d���m�F
	if (soundContainer.count(tag) != 0)
		return;

	soundContainer.emplace(tag, Sound::Load(path));

	//�ǂݍ��݂Ɏ��s���Ă�����A�T�[�g
	assert(soundContainer[tag]);
}

/**************************************
�N���A����
***************************************/
void SE::Clear()
{
	for (auto&& pair : soundContainer)
	{
		SAFE_RELEASE(pair.second);
	}
	soundContainer.clear();
}

/**************************************
�Đ�����
***************************************/
void SE::Play(int tag, float volume)
{
	//�o�^�m�F
	if (soundContainer.count(tag) == 0)
		return;

	LPDIRECTSOUNDBUFFER8 buffer = soundContainer[tag];
	Sound::SetVolume(buffer, volume);
	Sound::Play(buffer, Sound::E_DS8_FLAG_NONE, true);
}

/**************************************
��~����
***************************************/
void SE::Stop(int tag)
{
	//�o�^�m�F
	if (soundContainer.count(tag) == 0)
		return;

	Sound::Stop(soundContainer[tag]);
}

/**************************************
��~����
***************************************/
void SE::Stop()
{
	for (auto&& pair : soundContainer)
	{
		Sound::Stop(pair.second);
	}
}

/**************************************
�ĊJ����
***************************************/
void SE::Resume(int tag)
{
	//�o�^�m�F
	if (soundContainer.count(tag) == 0)
		return;

	//�~�܂��Ă����Ƃ��납��Đ��J�n
	Sound::Play(soundContainer[tag], Sound::E_DS8_FLAG_NONE, false);
}

/**************************************
�ĊJ����
***************************************/
void SE::Resume()
{
	for (auto&& pair : soundContainer)
	{
		Sound::Play(pair.second, Sound::E_DS8_FLAG_NONE, false);
	}
}

/**************************************
�Đ�������
***************************************/
bool SE::IsPlaying(int tag)
{
	if (soundContainer.count(tag) == 0)
		return false;

	//�X�e�[�^�X�擾
	return Sound::IsPlaying(soundContainer[tag]);
}
