//=====================================
//
// ランキング展開エフェクト処理[ExpandEffect.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _ExpandEffect_H_
#define _ExpandEffect_H_

#include "../../../main.h"
#include "../../../Framework/Particle/2D/Particle2D.h"
#include "../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	ExpandEffectControllerクラス
	***************************************/
	class ExpandEffectController : public BaseParticleController
	{
	public:
		ExpandEffectController();
		bool Draw(void) override;
	};

	/**************************************
	ExpandEffectクラス
	***************************************/
	class ExpandEffect : public Particle2D
	{
	public:
		ExpandEffect();
		~ExpandEffect();

		void Init();
		void Update();

	private:
		static const int Life;

		float targetScale;
	};
}
#endif