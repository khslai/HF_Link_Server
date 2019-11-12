//=====================================
//
//Template.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameIdle.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Tool/ProfilerCPU.h"

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameIdle::OnUpdate(GameScene & entity)
{
	//フィールド更新
	

	//イベント更新

	return State::Idle;
}

/**************************************
入場処理
***************************************/
void GameScene::GameIdle::OnStart(GameScene & entity)
{

}
