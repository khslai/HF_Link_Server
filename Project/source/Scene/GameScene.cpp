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
	// �J�����쐬
	fieldCamera = new FieldCamera();
	Camera::SetMainCamera(fieldCamera);
	// �J�����̒Ǐ]�ڕW�ɃJ�[�\����ݒ肵�ă��[�h�ؑ�
	fieldCamera->SetTargetPos(Vector3::Zero);
	fieldCamera->ChangeMode(FieldCamera::Mode::FrontSide);

	// �p�[�e�B�N��������
	ParticleManager = GameParticleManager::Instance();
	ParticleManager->Init();
	//ParticleManager->SetBlueDebris(D3DXVECTOR3(0.0f, 10.0f, 30.0f));

	// ���{�b�g�̏�����
	Robot = new RobotActor();

	// �T�[�o�[�̐ݒ�
	Server = new UDPServer();
	// �T�[�o�[��M�X���b�h�ݒ�
	UDPServer::Thread = (HANDLE)_beginthreadex(NULL, 0, UDPServer::ThreadEntryPoint, Server, 0, NULL);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	SAFE_DELETE(fieldCamera);
	SAFE_DELETE(Server);
	SAFE_DELETE(Robot);

	// �p�[�e�B�N���폜
	ParticleManager->Uninit();
}

/**************************************
�X�V����
***************************************/
void GameScene::Update()
{
	// �J�����X�V
	fieldCamera->Update();

	// �J�����̏����G�t�F�N�g�ɓn��
	SpriteEffect::SetView(fieldCamera->GetViewMtx());
	SpriteEffect::SetProjection(fieldCamera->GetProjectionMtx());

	// �T�[�o�[�X�V
	Server->Update();

	// ���{�b�g�X�V
	Robot->Update();

	// �p�[�e�B�N���X�V
	ParticleManager->Update();

	// �}���`�X���b�h�̎��s��҂�
	DWORD ThreadResult = WaitForSingleObject(UDPServer::Thread, 1);
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
