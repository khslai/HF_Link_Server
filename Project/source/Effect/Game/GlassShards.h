//=====================================
//
// �K���X�j�ЃG�t�F�N�g����[GlassShards.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _GlassShards_H_
#define _GlassShards_H_

#include "../../../main.h"
#include "../../../Framework/Particle/BaseParticleController.h"
#include "../../../Framework/Particle/2D/Particle2D.h"
#include "../../../Framework/Particle/3D/Particle3D.h"

namespace Effect::Game
{
	/**************************************
	GlassShardsController�N���X
	***************************************/
	class GlassShardsController : public BaseParticleController
	{
	public:
		GlassShardsController();
	};

	/**************************************
	GlassShards�N���X
	***************************************/
	class GlassShards : public Particle2D
	{
	public:
		static const int Life;
		static const float MinSpeed, MaxSpeed;
		static const int TexUV_U;
		static const int TexUV_V;

		GlassShards();

		void Init();
		void Update();

	private:

		const float InitSpeed;
		D3DXVECTOR3 moveDirection;
	};
}

#endif