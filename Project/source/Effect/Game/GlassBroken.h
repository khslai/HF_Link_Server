//=====================================
//
// スクリーン割れるエフェクト処理[GlassBroken.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _GlassBroken_H_
#define _GlassBroken_H_

#include "../../../main.h"
#include "../../../Framework/Particle/2D/Particle2D.h"
#include "../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	GlassBrokenControllerクラス
	***************************************/
	class GlassBrokenController : public BaseParticleController
	{
	public:
		GlassBrokenController();
	};

	/**************************************
	GlassBrokenクラス
	***************************************/
	class GlassBroken : public Particle2D
	{
	public:
		GlassBroken();
		~GlassBroken();

		void Init();
		void Update();

	private:
		static const int Life;
	};
}
#endif