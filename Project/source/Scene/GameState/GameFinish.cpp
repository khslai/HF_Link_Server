//=====================================
//
//GameFinish.cpp
//�@�\:�Q�[���V�[���I������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameFinish.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameFinish::OnStart(GameScene & entity)
{
	//�X�R�A�̕ۑ��Ƃ��I���e���b�v�̍Đ��Ƃ������
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameFinish::OnUpdate(GameScene & entity)
{
	//���͂Ƃ肠�������������
	State next = State::Finish;
	return next;
}
