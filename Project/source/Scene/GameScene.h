//=====================================
//
//GameScene.h
//機能:ゲームシーン処理
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#define _CRTDBG_MAP_ALLOC
#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include "../../Framework/Pattern/BaseState.h"
#include "../../Framework/Pattern/Delegate.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class FieldCamera;
class UDPServer;
class GameParticleManager;
class RobotActor;


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

private:
	FieldCamera* fieldCamera;					//フィールドカメラ
	GameParticleManager *ParticleManager;		// パーティクルマネージャー
	UDPServer *Server;							// サーバー
	RobotActor *Robot;
};
#endif