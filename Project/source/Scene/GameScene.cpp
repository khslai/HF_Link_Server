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

	//�p�[�e�B�N��������
	ParticleManager = GameParticleManager::Instance();
	ParticleManager->Init();
	//ParticleManager->SetBlueDebris(D3DXVECTOR3(0.0f, 10.0f, 30.0f));

	Robot = new RobotActor();

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

	//�X�e�[�g�}�V���폜
	Utility::DeleteContainer(fsm);

	// �T�[�o�[�폜
	SAFE_DELETE(Server);
	SAFE_DELETE(Robot);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	//�J�����X�V
	fieldCamera->Update();

	//�J�����̏����G�t�F�N�g�ɓn��
	SpriteEffect::SetView(fieldCamera->GetViewMtx());
	SpriteEffect::SetProjection(fieldCamera->GetProjectionMtx());

	Server->Update();

	Robot->Update();

	ParticleManager->Update();

	// �}���`�X���b�h�̎��s��҂�
	DWORD ThreadResult = WaitForSingleObject(UDPServer::Thread, 1);

	// �X�e�[�g���X�V
	State next = fsm[currentState]->OnUpdate(*this);
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	//�J�����Z�b�g
	fieldCamera->Set();

	// �w�i
	Server->DrawBackground();

	// ���{�b�g
	Robot->Draw();

	// �p�[�e�B�N��(3D)
	ParticleManager->Draw3DParticle();

	// �����L���O
	Server->DrawRanking();

	// �p�[�e�B�N��(2D)
	ParticleManager->Draw2DParticle();
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
}