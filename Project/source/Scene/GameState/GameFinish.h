//=====================================
//
//GameFinish.h
//�@�\:�Q�[���V�[���I������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEFINISH_H_
#define _GAMEFINISH_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameFinish : public GameScene::SceneState
{
public:
	State OnUpdate(GameScene& entity);
	void OnStart(GameScene& entity);
};
#endif