//=====================================
//
//GameFarView.h
//�@�\:�S�̂��������璭�߂�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEFARVIEW_H_
#define _GAMEFARVIEW_H_

#include "../../../main.h"
#include "../../../Framework/Pattern/BaseState.h"
#include "../GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameFarView : public GameScene::SceneState
{
public:
	void OnStart(GameScene& entity);
	State OnUpdate(GameScene& entity);
};

#endif