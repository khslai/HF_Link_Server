//=====================================
//
// �����q�G�t�F�N�g����[BlueDebris.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _BLUEDEBRIS_H_
#define _BLUEDEBRIS_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game
{
	/**************************************
	BlueDebrisController�N���X
	***************************************/
	class BlueDebrisController : public BaseParticleController
	{
	public:
		BlueDebrisController();
	};

	/**************************************
	BlueDebris�N���X
	***************************************/
	class BlueDebris : public Particle3D
	{
	public:
		static const int MinLife, MaxLife;
		static const float MinSpeed, MaxSpeed;
		static const int TexDiv;

		BlueDebris();

		void Init();
		void Update();

	private:

		const float InitSpeed;
		D3DXVECTOR3 moveDirection;
	};
}

#endif