//=====================================
//
//GamePause.h
//�@�\:�Q�[�����f�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEPAUSE_H_
#define _GAMEPAUSE_H_

#include "../../../main.h"
#include "../GameScene.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GamePause : public GameScene::SceneState
{
public:
	void OnStart(GameScene& entity);
	State OnUpdate(GameScene& entity);
};

#endif