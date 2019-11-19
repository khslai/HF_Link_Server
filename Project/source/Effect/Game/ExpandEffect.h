//=====================================
//
// �����L���O�W�J�G�t�F�N�g����[ExpandEffect.h]
// Author : HAL���� GP12B332 41 ���M��
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
	ExpandEffectController�N���X
	***************************************/
	class ExpandEffectController : public BaseParticleController
	{
	public:
		ExpandEffectController();
		bool Draw(void) override;
	};

	/**************************************
	ExpandEffect�N���X
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