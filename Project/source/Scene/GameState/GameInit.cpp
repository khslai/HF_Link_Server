//=====================================
//
//GameInit.cpp
//機能:
//Author:GP12B332 21 立花雄太
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
入場処理
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{	
	//カメラにプラグインを追加して初期化
	//entity.fieldCamera->AddPlugin(Camera::TranslationPlugin::Instance());
	//entity.fieldCamera->AddPlugin(Camera::ShakePlugin::Instance());
	Camera::TranslationPlugin::Instance()->Init();
	
	//カメラの追従目標にカーソルを設定してモード切替
	entity.fieldCamera->SetTargetPos(Vector3::Zero);
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::FrontSide);

	//トランジション画面をオフにして遷移
	//TransitionController::Instance()->SetTransition(true, TransitionType::HexaPop, [&]()
	//{
		entity.ChangeState(State::Idle);
	//});
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	return GameScene::State::Initialize;
}
