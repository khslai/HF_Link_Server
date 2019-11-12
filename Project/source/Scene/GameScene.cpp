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
#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"
#include "../EventActorBase.h"
#include "../Actor/PlaceActor.h"
#include "../Actor/CityActor.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Tool/ProfilerCPU.h"
#include "../../Framework/Core/SceneManager.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Network/UDPServer.h"

/**************************************
staticメンバ
***************************************/


/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	// メッシュ、テクスチャを読み込む
	LoadResource();

	//カメラ作成
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	//各インスタンス作成
	PlaceActorContainer.push_back(new CityActor(Vector3::Zero));
	Server = new UDPServer();
	// サーバー受信スレッド設定
	UDPServer::Thread = (HANDLE)_beginthreadex(NULL, 0, UDPServer::ThreadEntryPoint, Server, 0, NULL);

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();

	//ステート初期化
	ChangeState(State::Initialize);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//カメラ削除
	SAFE_DELETE(fieldCamera);

	//アクターコンテナ削除
	Utility::DeleteContainer(PlaceActorContainer);

	//ステートマシン削除
	Utility::DeleteContainer(fsm);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	//カメラ更新
	fieldCamera->Update();

	for (auto &Actor : PlaceActorContainer)
	{
		Actor->Update();
	}

	DWORD ThreadResult = WaitForSingleObject(UDPServer::Thread, 1);
	static int Count = 0;
	if (ThreadResult == WAIT_OBJECT_0)
	{
		// スレッド終了
	}
	else if (ThreadResult == WAIT_TIMEOUT)
	{
		Count++;
		// タイムアウト
	}
	Debug::Begin("UDP Server");
	Debug::Text("Second Thread Entry Count:%d", Count);
	Debug::End();

	//ステートを更新
	State next = fsm[currentState]->OnUpdate(*this);
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//カメラセット
	fieldCamera->Set();

	for (auto &Actor : PlaceActorContainer)
	{
		Actor->Draw();
	}

	Server->Draw();
}

/**************************************
ステート遷移処理
***************************************/
void GameScene::ChangeState(State next)
{
	prevState = currentState;

	currentState = next;

	if (fsm[currentState] != NULL)
	{
		fsm[currentState]->OnStart(*this);
	}
}

/**************************************
// メッシュ、テクスチャを読み込む
***************************************/
void GameScene::LoadResource(void)
{
	//ResourceManager::Instance()->LoadMesh("UFO", "data/MODEL/UFO/UFO.x");
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
}