//=====================================
//
// �X�N���[�������G�t�F�N�g����[GlassBroken.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "GlassBroken.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	GlassBrokenController::GlassBrokenController() :
		BaseParticleController(Particle_2D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		//�X�N���[�����W�ň����̂�Y�T�C�Y���}�C�i�X�ɂ��邱�Ƃɒ���
		const D3DXVECTOR2 SizeParticle{ 1920.0f, -1080.0f};
		MakeUnitBuffer(SizeParticle);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/GlassBroken.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const int MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new GlassBroken();
		}

		//�G�~�b�^�R���e�i�쐬
		const int MaxEmitter = 1;
		const int NumEmit = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit);
		}
	}

	/**************************************
	GlassBroken�R���X�g���N�^
	***************************************/
	const int GlassBroken::Life = 60;

	/**************************************
	GlassBroken�R���X�g���N�^
	***************************************/
	GlassBroken::GlassBroken() :
		Particle2D(Life)
	{
	}

	/**************************************
	GlassBroken�f�X�g���N�^
	***************************************/
	GlassBroken::~GlassBroken()
	{
	}

	/**************************************
	GlassBroken����������
	***************************************/
	void GlassBroken::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	GlassBroken�X�V����
	***************************************/
	void GlassBroken::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;
	}
}