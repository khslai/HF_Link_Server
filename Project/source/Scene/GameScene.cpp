//=====================================
//
//GameScene.cpp
//機能:ゲームシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../GameConfig.h"
#include "../Camera/FieldCamera.h"
#include "../Effect/GameParticleManager.h"
#include "../Actor/RobotActor.h"

#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Tool/ProfilerCPU.h"
#include "../../Framework/Core/SceneManager.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Network/UDPServer.h"
#include "../../Framework/Effect/SpriteEffect.h"
#include "../../Framework/Input/input.h"

/**************************************
staticメンバ
***************************************/


/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	// カメラ作成
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);
	// カメラの追従目標にカーソルを設定してモード切替
	fieldCamera->SetTargetPos(Vector3::Zero);
	fieldCamera->ChangeMode(FieldCamera::Mode::FrontSide);

	// パーティクル初期化
	ParticleManager = GameParticleManager::Instance();
	ParticleManager->Init();
	//ParticleManager->SetBlueDebris(D3DXVECTOR3(0.0f, 10.0f, 30.0f));

	// ロボットの初期化
	Robot = new RobotActor();

	// サーバーの設定
	Server = new UDPServer();
	// サーバー受信スレッド設定
	UDPServer::Thread = (HANDLE)_beginthreadex(NULL, 0, UDPServer::ThreadEntryPoint, Server, 0, NULL);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(fieldCamera);
	SAFE_DELETE(Server);
	SAFE_DELETE(Robot);

	// パーティクル削除
	ParticleManager->Uninit();
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	// カメラ更新
	fieldCamera->Update();

	// カメラの情報をエフェクトに渡す
	SpriteEffect::SetView(fieldCamera->GetViewMtx());
	SpriteEffect::SetProjection(fieldCamera->GetProjectionMtx());

	// サーバー更新
	Server->Update();

	// ロボット更新
	Robot->Update();

	// パーティクル更新
	ParticleManager->Update();

	// マルチスレッドの実行を待つ
	DWORD ThreadResult = WaitForSingleObject(UDPServer::Thread, 1);
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//カメラセット
	fieldCamera->Set();

	// 背景
	Server->DrawBackground();

	// ロボット
	Robot->Draw();

	// パーティクル(3D)
	ParticleManager->Draw3DParticle();

	// ランキング
	Server->DrawRanking();

	// パーティクル(2D)
	ParticleManager->Draw2DParticle();
}
