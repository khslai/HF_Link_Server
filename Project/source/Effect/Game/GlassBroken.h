//=====================================
//
// �X�N���[�������G�t�F�N�g����[GlassBroken.h]
// Author : HAL���� GP12B332 41 ���M��
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
	GlassBrokenController�N���X
	***************************************/
	class GlassBrokenController : public BaseParticleController
	{
	public:
		GlassBrokenController();
	};

	/**************************************
	GlassBroken�N���X
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