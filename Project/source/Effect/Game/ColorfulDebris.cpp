//=====================================
//
// �J���[���q�G�t�F�N�g����[ColorfulDebris.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "ColorfulDebris.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	�R���X�g���N�^
	***************************************/
	ColorfulDebrisController::ColorfulDebrisController() :
		BaseParticleController(Particle_2D)
	{
		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 SizeParticle = { 30.0f, -30.0f };
		const D3DXVECTOR2 DivParticle = { 4.0f, 4.0f };
		MakeUnitBuffer(SizeParticle, DivParticle);

		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/levelup.png");

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new ColorfulDebris();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 16;
		const int DurationEmit = 1;
		const int NumEmit = 30;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	ColorfulDebris�R���X�g���N�^
	***************************************/
	const int ColorfulDebris::Life = 60;

	/**************************************
	ColorfulDebris�R���X�g���N�^
	***************************************/
	ColorfulDebris::ColorfulDebris() :
		Particle2D(Life),
		speed(Math::RandomRange(5.0f, 15.0f))
		//initScale(Math::RandomRange(1.0f))
		//directionMove(Vector3::Down)
	{
	}

	/**************************************
	ColorfulDebris�f�X�g���N�^
	***************************************/
	ColorfulDebris::~ColorfulDebris()
	{
	}

	/**************************************
	ColorfulDebris����������
	***************************************/
	void ColorfulDebris::Init()
	{
		cntFrame = 0;
		active = true;

		int randomIndex = Math::RandomRange(0, 16);
		uv.u = randomIndex % 4 / 4.0f;
		uv.v = randomIndex / 4 / 4.0f;

		D3DXVECTOR3 BasePos = transform->GetPosition();
		float Length = Math::RandomRange(0.0f, 100.0f);
		D3DXVECTOR3 position = BasePos + D3DXVECTOR3{
			cosf(D3DXToRadian(Math::RandomRange(0.0f,360.0f))) * Length,
			sinf(D3DXToRadian(Math::RandomRange(0.0f,360.0f))) * Length,
			0.0f
		};
		position.z = 0.0f;
		transform->SetPosition(position);
	}

	/**************************************
	ColorfulDebris�X�V����
	***************************************/
	void ColorfulDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		// 2D��Y����3D��Y���͋t
		transform->Move(Vector3::Up * speed);
		//transform->Rotate(0.0f, 0.0f, 30.0f);
	}
}