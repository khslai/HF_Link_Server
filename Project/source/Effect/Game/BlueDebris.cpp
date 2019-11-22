//=====================================
//
// �����q�G�t�F�N�g����[BlueDebris.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "BlueDebris.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BlueDebrisController�R���X�g���N�^
	***************************************/
	BlueDebrisController::BlueDebrisController() :
		BaseParticleController(Particle_3D)
	{
		//�e�N�X�`���ǂݍ���
		LoadTexture("data/TEXTURE/Particle/blueDebris.png");

		//�P�ʒ��_�o�b�t�@�쐬
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f };
		const D3DXVECTOR2 TextureDiv{ (float)BlueDebris::TexDiv, (float)BlueDebris::TexDiv };
		MakeUnitBuffer(ParticleSize, TextureDiv);

		//�p�[�e�B�N���R���e�i�쐬
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new BlueDebris();
		}

		//�G�~�b�^�[�R���e�i�쐬
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, true);
		}
	}

	/**************************************
	BlueDebris statci�����o
	***************************************/
	const int BlueDebris::MinLife = 60;
	const int BlueDebris::MaxLife = 120;
	const float BlueDebris::MinSpeed = 0.05f;
	const float BlueDebris::MaxSpeed = 0.2f;
	const int BlueDebris::TexDiv = 3;

	/**************************************
	BlueDebris�R���X�g���N�^
	***************************************/
	BlueDebris::BlueDebris() :
		Particle3D(MinLife, MaxLife),
		InitSpeed(Math::RandomRange(MinSpeed, MaxSpeed)),
		moveDirection(Vector3::Zero)
	{
	}

	/**************************************
	BlueDebris����������
	***************************************/
	void BlueDebris::Init()
	{
		cntFrame = 0;
		active = true;

		//�X�P�[�����O
		float scale = Math::RandomRange(0.2f, 1.2f);
		transform->SetScale(Vector3::One * scale);

		//�ړ�������ݒ�
		//moveDirection = Vector3::Random();
		moveDirection = D3DXVECTOR3(
			Math::RandomRange(-0.5f, 0.5f),
			Math::RandomRange(-0.5f, 0.5f),
			Math::RandomRange(0.0f, -1.0f)
		);

		D3DXVec3Normalize(&moveDirection, &moveDirection);

		//UV���W������
		int indexUV = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = indexUV % TexDiv / (float)TexDiv;
		uv.v = indexUV / TexDiv / (float)TexDiv;

		//�����ʒu���ړ������փI�t�Z�b�g
		transform->Move(moveDirection);
	}

	/**************************************
	BlueDebris�X�V����
	***************************************/
	void BlueDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//�X�s�[�h���C�[�W���O�ŋ��߂Ĉړ��v�Z
		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, InitSpeed, MaxSpeed, EaseType::Linear);
		transform->Move(moveDirection * speed);

		//�X�P�[���v�Z
		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::Linear);
		transform->SetScale(Vector3::One * scale);

		//��]
		const float angleRotate = 10.0f;
		transform->Rotate(0.0f, 0.0f, angleRotate);
	}

}