//=============================================================================
//
// �Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _GAMEPARTICLEMANAGER_H_
#define _GAMEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�Q�[���V�[���̃p�[�e�B�N���ʂ��ԍ�
***************************************/
namespace GameParticle
{
	enum ID
	{
		ExpandEffect,		// �����L���O�W�J�̃G�t�F�N�g
		BlueDebris,			// �����q
		GlassShards,		// �K���X�j��
		GlassBroken,		// �X�N���[�������
		Max
	};
}

/**************************************
�N���X��`
***************************************/
class GameParticleManager : public SceneParticleManager, public BaseSingleton<GameParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	//����������
	void Init() override;

	//�`�揈��
	void Draw3DParticle() override;
	void Draw2DParticle() override;

	// �����L���O�W�J�̃G�t�F�N�g�Z�b�g����
	void SetExpandEffect(D3DXVECTOR3 Pos, std::function<void(void)> callback = nullptr);
	// �����q�G�t�F�N�g�Z�b�g����
	void SetBlueDebris(D3DXVECTOR3 Pos, std::function<void(void)> callback = nullptr);
	// �K���X�j�ЃG�t�F�N�g�Z�b�g����
	void SetGlassShards(D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f,0.0f,0.0f), std::function<void(void)> callback = nullptr);


};

#endif