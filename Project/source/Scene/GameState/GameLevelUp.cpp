//=====================================
//
//GameLevelUp.cpp
//�@�\:�Q�[���V�[�����x���A�b�v�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameLevelUp.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameLevelUp::OnStart(GameScene & entity)
{
	//TODO:���x���A�b�v���̉��o���Đ�����
	
	//���x���A�b�v����
	entity.OnLevelUp();
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameLevelUp::OnUpdate(GameScene & entity)
{
	return State::LevelUp;
}
