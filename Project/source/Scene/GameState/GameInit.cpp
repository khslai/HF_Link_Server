//=====================================
//
//GameInit.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameInit.h"
#include "../../GameConfig.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../../Framework/Camera/CameraShakePlugin.h"
#include "../../../Framework/Core/PlayerPrefs.h"

#include "../../Camera/FieldCamera.h"

/**************************************
���ꏈ��
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{	
	//�J�����Ƀv���O�C����ǉ����ď�����
	//entity.fieldCamera->AddPlugin(Camera::TranslationPlugin::Instance());
	//entity.fieldCamera->AddPlugin(Camera::ShakePlugin::Instance());
	Camera::TranslationPlugin::Instance()->Init();
	
	//�J�����̒Ǐ]�ڕW�ɃJ�[�\����ݒ肵�ă��[�h�ؑ�
	entity.fieldCamera->SetTargetPos(Vector3::Zero);
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::FrontSide);

	//�g�����W�V������ʂ��I�t�ɂ��đJ��
	//TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
	//{
		entity.ChangeState(State::Idle);
	//});
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	return GameScene::State::Initialize;
}
