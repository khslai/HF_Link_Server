//=====================================
//
//�V�[���p�[�e�B�N���}�l�[�W������[SceneParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SceneParticleManager.h"
#include "../PostEffect/CrossFilterController.h"
#include "../PostEffect/ScreenObject.h"
#include "BaseParticleController.h"
#include "../PostEffect/CrossFilterController.h"
#include "../Tool/DebugWindow.h"

/**************************************
�}�N����`
***************************************/
#define SCENEMPARTICLEMANAGER_LABEL		"ParticleManager"

/**************************************
�R���X�g���N�^
***************************************/
SceneParticleManager::SceneParticleManager() :
	renderTexture(NULL),
	renderSurface(NULL),
	screenObj(NULL),
	oldSuf(NULL),
	initialized(false)
{
}

/**************************************
����������
***************************************/
void SceneParticleManager::Init()
{
	//�V���O���g�����̂��߁A�����Ń��\�[�X���쐬
	if (!initialized)
	{
		CreateRenderTarget();
		initialized = true;
		crossFilter = new CrossFilterController();
	}
}

/**************************************
�I������
***************************************/
void SceneParticleManager::Uninit()
{
	for (auto& controller : controllers)
	{
		controller->Uninit();
	}

	//�V���O���g���̂��߂����Ń��\�[�X���
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);
	SAFE_DELETE(crossFilter);

	Utility::DeleteContainer(controllers);

	initialized = false;
}

/**************************************
�X�V����
***************************************/
void SceneParticleManager::Update()
{
	for (auto& controller : controllers)
	{
		controller->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void SceneParticleManager::Draw3DParticle()
{
	//�����_�[�p�����[�^�؂�ւ�
	ChangeRenderParameter();

	//�C���X�^���V���O�`��J�n
	BaseParticleController::BeginDraw();

	//�`��
	bool isDrewd = false;
	for (auto& controller : controllers)
	{
		if (controller->GetParticleType() == BaseParticleController::Particle_3D)
		{
			isDrewd |= controller->Draw();
		}
	}

	//�C���X�^���V���O�`��I��
	BaseParticleController::EndDraw();

	//���ׂĂ̌��ʂ����̃����_�[�^�[�Q�b�g�ɕ`��
	RestoreRenderParameter();
	screenObj->Draw();

	//�����[�X�ł̂݃N���X�t�B���^��K�p����
#ifndef _DEBUG	
	if (isDrewd)
		crossFilter->Draw(renderTexture);
#endif

	//�����_�[�X�e�[�g����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void SceneParticleManager::Draw2DParticle()
{
	//�����_�[�p�����[�^�؂�ւ�
	ChangeRenderParameter();

	//�C���X�^���V���O�`��J�n
	BaseParticleController::BeginDraw();

	//�`��
	bool isDrewd = false;
	for (auto& controller : controllers)
	{
		if (controller->GetParticleType() == BaseParticleController::Particle_2D)
		{
			isDrewd |= controller->Draw();
		}
	}

	//�C���X�^���V���O�`��I��
	BaseParticleController::EndDraw();

	//���ׂĂ̌��ʂ����̃����_�[�^�[�Q�b�g�ɕ`��
	RestoreRenderParameter();
	screenObj->Draw();

	//�����_�[�X�e�[�g����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

/**************************************
��������
***************************************/
BaseEmitter* SceneParticleManager::Generate(UINT id, const D3DXVECTOR3& pos, std::function<void(void)> callback)
{
	assert(id >= 0 && id < controllers.size());

	return controllers[id]->SetEmitter(pos, callback);
}

/**************************************
��������
***************************************/
BaseEmitter* SceneParticleManager::Generate(UINT id, const Transform& transform, std::function<void(void)> callback)
{
	assert(id >= 0 && id < controllers.size());

	return controllers[id]->SetEmitter(transform, callback);
}

/**************************************
�����_�[�^�[�Q�b�g�쐬����
***************************************/
void SceneParticleManager::CreateRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�쐬
	pDevice->CreateTexture(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	//�T�[�t�F�C�X�擾
	renderTexture->GetSurfaceLevel(0, &renderSurface);

	//�r���[�|�[�g�쐬
	pDevice->GetViewport(&viewPort);
	viewPort.Width = SCREEN_WIDTH;
	viewPort.Height = SCREEN_HEIGHT;

	//�`��p�X�N���[���I�u�W�F�N�g�쐬
	screenObj = new ScreenObject(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**************************************
�����_�[�p�����[�^�ύX����
***************************************/
void SceneParticleManager::ChangeRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g���L���b�V��
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->GetViewport(&oldViewport);

	//�����_�[�^�[�Q�b�g�؂�ւ�
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->SetViewport(&viewPort);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);

	//�����_�[�X�e�[�g�؂�ւ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
}

/**************************************
�����_�[�p�����[�^��������
***************************************/
void SceneParticleManager::RestoreRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, oldSuf);
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetViewport(&oldViewport);
	SAFE_RELEASE(oldSuf);
}