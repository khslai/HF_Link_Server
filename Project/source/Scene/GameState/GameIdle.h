//=====================================
//
//GameIdle.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEIDLE_H_
#define _GAMEIDLE_H_

#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameIdle : public BaseState<GameScene, GameScene::State>
{
	virtual State OnUpdate(GameScene& entity) override;
	virtual void OnStart(GameScene& entity) override;
};
#endif