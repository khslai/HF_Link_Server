//=====================================
//
// ガイドアクター[GuideViewer.h]
// 機能：ガイド役キャラクター
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "RobotActor.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Tween/Tween.h"

//=====================================
// スタティックメンバ初期化
//=====================================
const RobotActor::AnimData RobotActor::data[] = {
	{"Idle",			1.0f, 0.3f, 1 / 60.0f, Idle},		// 待機
	{"Cheering",		1.0f, 0.3f, 1 / 60.0f, Idle},		// レベルアップ
	{"Clapping",		1.0f, 0.3f, 1 / 60.0f, Idle},		// ランキング追加
	{"Excited",			1.0f, 0.3f, 1 / 60.0f, Idle},		// レベルアップ
	{"FistPump",		1.0f, 0.3f, 1 / 60.0f, Idle},		// ランキング追加
	{"Pain",			1.0f, 0.3f, 1 / 60.0f, Idle},		// AIストライキ
	{"Waving",			1.0f, 0.3f, 1 / 60.0f, Idle},		// 待機
	{"Yeah",			1.0f, 0.3f, 1 / 60.0f, Idle},		// ランキング追加
	{"ShakeFist",		1.0f, 0.3f, 1 / 60.0f, Idle},		// 新しい町
	{"Salute",			1.0f, 0.3f, 1 / 60.0f, Idle},		// 待機
	{"WaveHand",		1.0f, 0.3f, 1 / 60.0f, Idle},		// 待機
	{"Defeat",			1.0f, 0.3f, 1 / 60.0f, Idle},
	{"Surprised",		1.0f, 0.3f, 1 / 60.0f, Idle},		// 新しい町
	{"TalkingTypeA",	1.0f, 0.3f, 1 / 60.0f, Idle},		// 待機
	{"TalkingTypeB",	1.0f, 0.3f, 1 / 60.0f, Idle},		// 宇宙人襲来
	{"SecretTalk",		1.0f, 0.3f, 1 / 60.0f, Idle},
	{"FightingIdle",	1.0f, 0.3f, 1 / 60.0f, Rush},
	{"Rush",			1.0f, 0.3f, 1 / 60.0f, Idle},		// 隕石
};

const char* RobotActor::FileName = "data/MODEL/Robot.X";
AnimationManager* RobotActor::anim = nullptr;

//=====================================
// コンストラクタ
//=====================================
RobotActor::RobotActor()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 20.0f));
	transform->SetScale(Vector3::One * 0.3f);
	transform->SetRotation(Vector3::Zero);
	SetActive(true);

	// アニメーションの作成
	anim = new AnimationManager();
	anim->LoadXFile(FileName, "Guide");

	// アニメーションセットの作成
	for (int i = 0; i < AnimMax; i++)
	{
		anim->LoadAnimation(data[AnimState(i)].tag, i, data[AnimState(i)].shiftTime);
		anim->SetPlaySpeed(i, data[AnimState(i)].playSpeed);
		anim->SetDeltaTime(i, data[AnimState(i)].deltaTime);
		anim->SetFinishTransition(i, data[AnimState(i)].NextAction);
	}

	//// アニメーション遷移のセット
	//for (int i = 0; i < AnimMax; i++)
	//{
	//	// パンチ連打とファイティングポーズだけはずっと続ける
	//	if (i == Rush || i == FightingIdle)
	//	{
	//		anim->SetFinishTransition(AnimState(i), AnimState(i));
	//	}
	//	// とりあえず全部アニメーション終了したらアイドルに戻す
	//	else
	//	{
	//		anim->SetFinishTransition(AnimState(i), AnimState(0));
	//	}
	//}
}

//=====================================
// デストラクタ
//=====================================
RobotActor::~RobotActor()
{
	//animのデストラクタは不要
	SAFE_DELETE(anim);
}

//=====================================
// 更新
//=====================================
void RobotActor::Update()
{
	anim->Update();

#if _DEBUG
	//Debug();
#endif
}

//=====================================
// 描画
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
// アニメーション切り替え
//=====================================
void RobotActor::ChangeAnim(AnimState next)
{
	anim->ChangeAnim((UINT)next, true);
}

#if _DEBUG
//=====================================
// デバッグ
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