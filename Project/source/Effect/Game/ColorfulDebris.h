//=====================================
//
// �J���[���q�G�t�F�N�g����[ColorfulDebris.h]
// Author : HAL���� GP12B332 41 ���M��
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
	ColorfulDebrisController�N���X
	***************************************/
	class ColorfulDebrisController : public BaseParticleController
	{
	public:
		ColorfulDebrisController();
	};

	/**************************************
	ColorfulDebris�N���X
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