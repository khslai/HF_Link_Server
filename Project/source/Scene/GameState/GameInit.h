//=====================================
//
//GameInit.h
//�@�\:�Q�[���V�[��������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEINIT_H_
#define _GAMEINIT_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameInit : public BaseState<GameScene, GameScene::State>
{
public:
	void OnStart(GameScene &entity);
	GameScene::State OnUpdate(GameScene &entity);
};

#endif