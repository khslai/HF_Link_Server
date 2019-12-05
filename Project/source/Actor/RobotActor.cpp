//=====================================
//
// �K�C�h�A�N�^�[[GuideViewer.h]
// �@�\�F�K�C�h���L�����N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "RobotActor.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Tween/Tween.h"

//=====================================
// �X�^�e�B�b�N�����o������
//=====================================
const RobotActor::AnimData RobotActor::data[] = {
	{"Idle",			1.0f, 0.3f, 1 / 60.0f, Idle},		// �ҋ@
	{"Cheering",		1.0f, 0.3f, 1 / 60.0f, Idle},		// ���x���A�b�v
	{"Clapping",		1.0f, 0.3f, 1 / 60.0f, Idle},		// �����L���O�ǉ�
	{"Excited",			1.0f, 0.3f, 1 / 60.0f, Idle},		// ���x���A�b�v
	{"FistPump",		1.0f, 0.3f, 1 / 60.0f, Idle},		// �����L���O�ǉ�
	{"Pain",			1.0f, 0.3f, 1 / 60.0f, Idle},		// AI�X�g���C�L
	{"Waving",			1.0f, 0.3f, 1 / 60.0f, Idle},		// �ҋ@
	{"Yeah",			1.0f, 0.3f, 1 / 60.0f, Idle},		// �����L���O�ǉ�
	{"ShakeFist",		1.0f, 0.3f, 1 / 60.0f, Idle},		// �V������
	{"Salute",			1.0f, 0.3f, 1 / 60.0f, Idle},		// �ҋ@
	{"WaveHand",		1.0f, 0.3f, 1 / 60.0f, Idle},		// �ҋ@
	{"Defeat",			1.0f, 0.3f, 1 / 60.0f, Idle},
	{"Surprised",		1.0f, 0.3f, 1 / 60.0f, Idle},		// �V������
	{"TalkingTypeA",	1.0f, 0.3f, 1 / 60.0f, Idle},		// �ҋ@
	{"TalkingTypeB",	1.0f, 0.3f, 1 / 60.0f, Idle},		// �F���l�P��
	{"SecretTalk",		1.0f, 0.3f, 1 / 60.0f, Idle},
	{"FightingIdle",	1.0f, 0.3f, 1 / 60.0f, Rush},
	{"Rush",			1.0f, 0.3f, 1 / 60.0f, Idle},		// 覐�
};

const char* RobotActor::FileName = "data/MODEL/Robot.X";
AnimationManager* RobotActor::anim = nullptr;

//=====================================
// �R���X�g���N�^
//=====================================
RobotActor::RobotActor()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 20.0f));
	transform->SetScale(Vector3::One * 0.3f);
	transform->SetRotation(Vector3::Zero);
	SetActive(true);

	// �A�j���[�V�����̍쐬
	anim = new AnimationManager();
	anim->LoadXFile(FileName, "Guide");

	// �A�j���[�V�����Z�b�g�̍쐬
	for (int i = 0; i < AnimMax; i++)
	{
		anim->LoadAnimation(data[AnimState(i)].tag, i, data[AnimState(i)].shiftTime);
		anim->SetPlaySpeed(i, data[AnimState(i)].playSpeed);
		anim->SetDeltaTime(i, data[AnimState(i)].deltaTime);
		anim->SetFinishTransition(i, data[AnimState(i)].NextAction);
	}

	//// �A�j���[�V�����J�ڂ̃Z�b�g
	//for (int i = 0; i < AnimMax; i++)
	//{
	//	// �p���`�A�łƃt�@�C�e�B���O�|�[�Y�����͂����Ƒ�����
	//	if (i == Rush || i == FightingIdle)
	//	{
	//		anim->SetFinishTransition(AnimState(i), AnimState(i));
	//	}
	//	// �Ƃ肠�����S���A�j���[�V�����I��������A�C�h���ɖ߂�
	//	else
	//	{
	//		anim->SetFinishTransition(AnimState(i), AnimState(0));
	//	}
	//}
}

//=====================================
// �f�X�g���N�^
//=====================================
RobotActor::~RobotActor()
{
	//anim�̃f�X�g���N�^�͕s�v
	SAFE_DELETE(anim);
}

//=====================================
// �X�V
//=====================================
void RobotActor::Update()
{
	anim->Update();

#if _DEBUG
	//Debug();
#endif
}

//=====================================
// �`��
//=====================================
void RobotActor::Draw()
{
	if (!IsActive())
		return;

	D3DXMATRIX mtxWorld = transform->GetMatrix();
	transform->SetWorld();

	anim->Draw(&mtxWorld);
}

//=====================================
// �A�j���[�V�����؂�ւ�
//=====================================
void RobotActor::ChangeAnim(AnimState next)
{
	anim->ChangeAnim((UINT)next, true);
}

#if _DEBUG
//=====================================
// �f�o�b�O
//=====================================
void RobotActor::Debug()
{
	Debug::Begin("RobotActorAnimation");

	if (Debug::Button("Cheering"))
	{
		anim->ChangeAnim(Cheering);
	}
	if (Debug::Button("Clapping"))
	{
		anim->ChangeAnim(Clapping);
	}
	if (Debug::Button("Excited"))
	{
		anim->ChangeAnim(Excited);
	}
	if (Debug::Button("FistPump"))
	{
		anim->ChangeAnim(FistPump);
	}
	if (Debug::Button("Pain"))
	{
		anim->ChangeAnim(Pain);
	}
	if (Debug::Button("Waving"))
	{
		anim->ChangeAnim(Waving);
	}
	if (Debug::Button("Yeah"))
	{
		anim->ChangeAnim(Yeah);
	}
	if (Debug::Button("ShakeFist"))
	{
		anim->ChangeAnim(ShakeFist);
	}
	if (Debug::Button("Salute"))
	{
		anim->ChangeAnim(Salute);
	}
	if (Debug::Button("WaveHand"))
	{
		anim->ChangeAnim(WaveHand);
	}
	if (Debug::Button("Defeat"))
	{
		anim->ChangeAnim(Defeat);
	}
	if (Debug::Button("Surprised"))
	{
		anim->ChangeAnim(Surprised);
	}
	if (Debug::Button("TalkingTypeA"))
	{
		anim->ChangeAnim(TalkingTypeA);
	}
	if (Debug::Button("TalkingTypeB"))
	{
		anim->ChangeAnim(TalkingTypeB);
	}
	if (Debug::Button("SecretTalk"))
	{
		anim->ChangeAnim(SecretTalk);
	}
	if (Debug::Button("FightingIdle"))
	{
		anim->ChangeAnim(FightingIdle);
	}
	if (Debug::Button("Rush"))
	{
		anim->ChangeAnim(Rush);
	}

	Debug::End();
}
#endif