//=====================================
//
//GameScene.h
//機能:ゲームシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include "../../Framework/Pattern/BaseState.h"
#include "../../Framework/Pattern/Delegate.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class FieldCamera;
class EventActorBase;
class PlaceActor;
class UDPServer;

/**************************************
クラス定義
***************************************/
class GameScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//ステートを表す列挙子
	enum State
	{
		Initialize,
		Idle,
		Max
	};

	//ステート遷移処理
	void ChangeState(State next);

private:
	using SceneState = BaseState<GameScene, State>;

	//シーンステートマシン
	std::vector<SceneState*> fsm;
	std::vector<PlaceActor*> PlaceActorContainer;
	State currentState, prevState;
	FieldCamera* fieldCamera;					//フィールドカメラ
	EventActorBase *EventActor;

	UDPServer *Server;

	//各ステートクラス
	class GameInit;
	class GameIdle;

	// メッシュ、テクスチャを読み込む
	void LoadResource(void);
};
#endif