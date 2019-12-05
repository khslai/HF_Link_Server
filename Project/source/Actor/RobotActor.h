//=============================================================================
//
// ���{�b�g�N���X [RobotActor.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _RobotActor_H_
#define _RobotActor_H_

#include "../../Framework/Core/GameObject.h"
#include "../../Framework/Animation/AnimationManager.h"

//**************************************
// �N���X��`
//**************************************
class RobotActor : public GameObject
{
public:
	RobotActor();
	~RobotActor();

	// �A�j���[�V�����X�e�[�g
	enum AnimState
	{
		Idle,
		Cheering,		// �E�����グ�ĐU��
		Clapping,		// ����
		Excited,		// ����킿��킿��炫��낫���
		FistPump,		// �E��ŃO�b�ƃK�b�c�|�[�Y
		Pain,			// ���ɒɂ݂�
		Waving,			// ���A�ǂ����ǂ���
		Yeah,			// ����ŃO�b�ƃK�b�c�|�[�Y
		ShakeFist,		// �E����グ�ĐU��
		Salute,			// �h��
		WaveHand,		// ��̑O�Ŏ���ӂ�i���₢��Ȃ��Ȃ��A�݂����ȁj
		Defeat,			// �����ŕ����Ă����[���Ċ���
		Surprised,		// �����[�I�H
		TalkingTypeA,	// ������L���ăA�s�[�����Ȃ���b��
		TalkingTypeB,	// �d�b���Ă銴��
		SecretTalk,		// �����b
		FightingIdle,	// �t�@�C�e�B���O�|�[�Y
		Rush,			// �p���`�A��

		// �ő吔
		AnimMax
	};

	// �A�j���[�V�����ǂݍ��݃f�[�^�p�\����
	struct AnimData
	{
		const char* tag;
		float playSpeed;
		float shiftTime;
		float deltaTime;
		int NextAction;
	};

	void Update();
	void Draw();

	static void ChangeAnim(AnimState next);

private:
	static AnimationManager* anim;					// �A�j���[�V�����}�l�[�W��
	static const AnimData data[AnimMax];	// �A�j���[�V�����ǂݍ��ݗp�f�[�^
	static const char* FileName;			// �ǂݍ���X�t�@�C��

#if _DEBUG
	void Debug();
#endif
};

#endif
