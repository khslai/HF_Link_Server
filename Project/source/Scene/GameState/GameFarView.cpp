//=====================================
//
//GameFarView.cpp
//�@�\:�Q�[�����������璭�߂�X�e�[�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameFarView.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../../Framework/Input/input.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameFarView::OnStart(GameScene & entity)
{
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::FarView);
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameFarView::OnUpdate(GameScene & entity)
{
	//�e�I�u�W�F�N�g�X�V
	entity.field->UpdateLogic();
	entity.field->UpdateObject();

	//�C�x���g�X�V
	entity.eventController->Update();

	//�������ԃJ�E���g
	entity.remainTime = Math::Max(0, --entity.remainTime);

	//�c�莞�Ԃ�0�ɂȂ�����I��
	if (entity.remainTime == 0)
	{
		entity.ChangeState(State::Finish);
	}
	//AI���W���x�����ő�ɓ��B���Ă����烌�x���A�b�v
	else if (entity.field->ShouldLevelUp())
	{
		entity.ChangeState(State::LevelUp);
	}
	//���_�ύX�{�^���������ꂽ��Idle���[�h�֑J��
	else if (entity.field->ShouldSwicthCamera())
	{
		entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);
		entity.ChangeState(State::Idle);
	}

	return State::FarView;
}
