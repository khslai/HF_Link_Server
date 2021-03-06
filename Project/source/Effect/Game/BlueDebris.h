//=====================================
//
// 青い粒子エフェクト処理[BlueDebris.h]
// Author : HAL東京 GP12B332 41 頼凱興
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
	BlueDebrisControllerクラス
	***************************************/
	class BlueDebrisController : public BaseParticleController
	{
	public:
		BlueDebrisController();
	};

	/**************************************
	BlueDebrisクラス
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