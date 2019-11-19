//=====================================
//
// �Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "Game/ExpandEffect.h"

/**************************************
static�����o
***************************************/


/**************************************
����������
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameParticle::Max, NULL);
	controllers[GameParticle::ExpandEffect] = new Effect::Game::ExpandEffectController();
}

/**************************************
�`�揈��
***************************************/
void GameParticleManager::Draw()
{
	SceneParticleManager::Draw();
}

/**************************************
�����L���O�W�J�̃G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetExpandEffect(D3DXVECTOR3 Pos, std::function<void(void)> callback)
{
	controllers[GameParticle::ExpandEffect]->SetEmitter(Pos, nullptr);
}
