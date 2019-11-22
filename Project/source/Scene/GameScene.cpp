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
#include "../Effect/GameParticleManager.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Tool/ProfilerCPU.h"
#include "../../Framework/Core/SceneManager.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Network/UDPServer.h"
#include "../../Framework/Effect/SpriteEffect.h"

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

	//�p�[�e�B�N��������
	ParticleManager = GameParticleManager::Instance();
	ParticleManager->Init();
	ParticleManager->SetBlueDebris(D3DXVECTOR3(0.0f, 10.0f, 30.0f));

	// �T�[�o�[�̐ݒ�
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

	//�p�[�e�B�N���폜
	ParticleManager->Uninit();

	//�A�N�^�[�R���e�i�폜
	Utility::DeleteContainer(PlaceActorContainer);

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);

	// �T�[�o�[�폜
	SAFE_DELETE(Server);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	//�J�����X�V
	fieldCamera->Update();

	D3DXVECTOR3 LeftUp = Camera::UnProjection(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f);
	D3DXVECTOR3 RightUp = Camera::UnProjection(D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f), 0.0f);
	D3DXVECTOR3 LeftDown = Camera::UnProjection(D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f), 0.0f);
	D3DXVECTOR3 RightDown = Camera::UnProjection(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 0.0f);
	D3DXVECTOR3 LeftCenter = Camera::UnProjection(D3DXVECTOR3(0.0f, SCREEN_CENTER_Y, 0.0f), 0.0f);

	//�J�����̏����G�t�F�N�g�ɓn��
	SpriteEffect::SetView(fieldCamera->GetViewMtx());
	SpriteEffect::SetProjection(fieldCamera->GetProjectionMtx());

	for (auto &Actor : PlaceActorContainer)
	{
		Actor->Update();
	}

	Server->Update();

	ParticleManager->Update();

	// �}���`�X���b�h�̎��s��҂�
	DWORD ThreadResult = WaitForSingleObject(UDPServer::Thread, 1);
	//if (ThreadResult == WAIT_OBJECT_0)
	//{
	//	// �X���b�h�I��
	//}
	//else if (ThreadResult == WAIT_TIMEOUT)
	//{
	//	// �^�C���A�E�g
	//}

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

	Server->DrawBackground();

	ParticleManager->Draw();

	Server->DrawRanking();
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