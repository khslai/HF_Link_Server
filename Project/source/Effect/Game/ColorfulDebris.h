//=====================================
//
// カラー粒子エフェクト処理[ColorfulDebris.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _ColorfulDebris_H_
#define _ColorfulDebris_H_

#include "../../../main.h"
#include "../../../Framework/Particle/2D/Particle2D.h"
#include "../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	ColorfulDebrisControllerクラス
	***************************************/
	class ColorfulDebrisController : public BaseParticleController
	{
	public:
		ColorfulDebrisController();
	};

	/**************************************
	ColorfulDebrisクラス
	***************************************/
	class ColorfulDebris : public Particle2D
	{
	public:
		ColorfulDebris();
		~ColorfulDebris();

		void Init();
		void Update();

	private:
		static const int Life;
		D3DXVECTOR3 directionMove;
		float speed;
		float initScale;
	};
}
#endif