//=====================================
//
// �����L���O�W�J�G�t�F�N�g����[ExpandEffect.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "ExpandEffect.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	ExpandEffectController::ExpandEffectController() :
		BaseParticleController(Particle_2D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		//�X�N���[�����W�ň����̂�Y�T�C�Y���}�C�i�X�ɂ��邱�Ƃɒ���
		const D3DXVECTOR2 SizeParticle{ 50.0f, -50.0f };
		MakeUnitBuffer(SizeParticle);

		//�e�N�X�`���ǂݍ���
		const char* Path = "data/TEXTURE/Particle/MoveTail.png";
		LoadTexture(Path);

		//�p�[�e�B�N���R���e�i�쐬
		const int MaxParticle = 32;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new ExpandEffect();
		}

		//�G�~�b�^�R���e�i�쐬
		const int MaxEmitter = 2;
		const int NumEmit = 32;
		const int DurationEmit = 60;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	�`��
	***************************************/
	//bool ExpandEffectController::Draw(void)
	//{
	//	bool Result = false;
	//	LPDIRECT3DDEVICE9 Device = GetDevice();

	//	//�����_�[�X�e�[�g�����Z�����ɐݒ�
	//	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	Result = BaseParticleController::Draw();

	//	//�����_�[�X�e�[�g�����ɖ߂�
	//	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//	return Result;
	//}

	/**************************************
	ExpandEffect�R���X�g���N�^
	***************************************/
	const int ExpandEffect::Life = 60;

	/**************************************
	ExpandEffect�R���X�g���N�^
	***************************************/
	ExpandEffect::ExpandEffect() :
		Particle2D(Life)
	{
	}

	/**************************************
	ExpandEffect�f�X�g���N�^
	***************************************/
	ExpandEffect::~ExpandEffect()
	{
	}

	/**************************************
	ExpandEffect����������
	***************************************/
	void ExpandEffect::Init()
	{
		cntFrame = 0;
		active = true;

		D3DXVECTOR3 BasePos = transform->GetPosition();
		D3DXVECTOR3 position{
			BasePos.x,
			BasePos.y + Math::RandomRange(-60.0f, 60.0f),
			0.0f
		};
		transform->SetPosition(position);
	}

	/**************************************
	ExpandEffect�X�V����
	***************************************/
	void ExpandEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		D3DXVECTOR3 Pos = transform->GetPosition();
		Pos.x = Easing::EaseValue(t, 0.0f, (float)SCREEN_WIDTH, EaseType::InQuart);
		transform->SetPosition(Pos);
	}
}