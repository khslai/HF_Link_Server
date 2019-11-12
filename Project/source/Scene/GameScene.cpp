//=====================================
//
//GameScene.cpp
//�@�\:�Q�[���V�[��
//Author:GP12B332 21 ���ԗY��
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
static�����o
***************************************/


/**************************************
����������
***************************************/
void GameScene::Init()
{
	// ���b�V���A�e�N�X�`����ǂݍ���
	LoadResource();

	//�J�����쐬
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);

	//�e�C���X�^���X�쐬
	PlaceActorContainer.push_back(new CityActor(Vector3::Zero));
	Server = new UDPServer();
	// �T�[�o�[��M�X���b�h�ݒ�
	UDPServer::Thread = (HANDLE)_beginthreadex(NULL, 0, UDPServer::ThreadEntryPoint, Server, 0, NULL);

	//�X�e�[�g�}�V���쐬
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();

	//�X�e�[�g������
	ChangeState(State::Initialize);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�J�����폜
	SAFE_DELETE(fieldCamera);

	//�A�N�^�[�R���e�i�폜
	Utility::DeleteContainer(PlaceActorContainer);

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	//�J�����X�V
	fieldCamera->Update();

	for (auto &Actor : PlaceActorContainer)
	{
		Actor->Update();
	}

	DWORD ThreadResult = WaitForSingleObject(UDPServer::Thread, 1);
	static int Count = 0;
	if (ThreadResult == WAIT_OBJECT_0)
	{
		// �X���b�h�I��
	}
	else if (ThreadResult == WAIT_TIMEOUT)
	{
		Count++;
		// �^�C���A�E�g
	}
	Debug::Begin("UDP Server");
	Debug::Text("Second Thread Entry Count:%d", Count);
	Debug::End();

	//�X�e�[�g���X�V
	State next = fsm[currentState]->OnUpdate(*this);
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	//�J�����Z�b�g
	fieldCamera->Set();

	for (auto &Actor : PlaceActorContainer)
	{
		Actor->Draw();
	}

	Server->Draw();
}

/**************************************
�X�e�[�g�J�ڏ���
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
// ���b�V���A�e�N�X�`����ǂݍ���
***************************************/
void GameScene::LoadResource(void)
{
	//ResourceManager::Instance()->LoadMesh("UFO", "data/MODEL/UFO/UFO.x");
	ResourceManager::Instance()->LoadMesh("Town-City", "data/MODEL/PlaceActor/Town.x");
}