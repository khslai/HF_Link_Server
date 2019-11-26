//=====================================
//
// �K���X�j�ЃG�t�F�N�g����[GlassShards.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "GlassShards.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	GlassShardsController�R���X�g���N�^
	***************************************/
	GlassShardsController::GlassShardsController() :
		BaseParticleController(Particle_2D)
		//BaseParticleController(Particle_3D)
	{
		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/GlassShards.png");

		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 ParticleSize{ 200.0f, -200.0f };
		const D3DXVECTOR2 TextureDiv{ 3.0f, 2.0f };
		MakeUnitBuffer(ParticleSize, TextureDiv);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new GlassShards();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 1;
		const int NumEmit = 32;
		const int EmitDuration = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, EmitDuration);
		}
	}

	/**************************************
	GlassShards statci�����o
	***************************************/
	const int GlassShards::Life = 60;
	const int GlassShards::TexUV_U = 3;
	const int GlassShards::TexUV_V = 2;
	const float GlassShards::MinSpeed = 10.0f;
	const float GlassShards::MaxSpeed = 30.0f;

	/**************************************
	GlassShards�R���X�g���N�^
	***************************************/
	GlassShards::GlassShards() :
		Particle2D(Life),
		InitSpeed(MaxSpeed),
		moveDirection(Vector3::Zero)
	{
	}

	/**************************************
	GlassShards����������
	***************************************/
	void GlassShards::Init()
	{
		cntFrame = 0;
		active = true;

		//�X�P�[�����O
		float scale = Math::RandomRange(0.5f, 1.0f);
		transform->SetScale(Vector3::One * scale);

		//�ړ�������ݒ�
		//moveDirection = Vector3::Random();
		moveDirection = D3DXVECTOR3(
			Math::RandomRange(-1.0f, 1.0f),
			Math::RandomRange(-1.0f, 1.0f),
			0.0f
		);

		D3DXVec3Normalize(&moveDirection, &moveDirection);
		//�����ʒu���ړ������փI�t�Z�b�g
		transform->Move(moveDirection);

		//UV���W������
		int indexUV = Math::RandomRange(0, TexUV_U * TexUV_V);
		uv.u = indexUV % TexUV_U / (float)TexUV_U;
		uv.v = indexUV / TexUV_U / (float)TexUV_V;
	}

	/**************************************
	GlassShards�X�V����
	***************************************/
	void GlassShards::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�X�s�[�h���C�[�W���O�ŋ��߂Ĉړ��v�Z
		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, MaxSpeed, MinSpeed, EaseType::OutQuart);
		if (cntFrame >= lifeFrame - 5)
		{
			speed = MaxSpeed * 0.8f;
		}
		transform->Move(moveDirection * speed);

		//��]
		float DegreeZ = Easing::EaseValue(t, 10.0f, 1.0f, EaseType::OutQuart);
		transform->Rotate(0.0f, 0.0f, DegreeZ);
	}
}