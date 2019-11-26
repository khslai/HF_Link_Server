//=====================================
//
// ガラス破片エフェクト処理[GlassShards.h]
// Author : HAL東京 GP12B332 41 頼凱興
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
	GlassShardsControllerクラス
	***************************************/
	class GlassShardsController : public BaseParticleController
	{
	public:
		GlassShardsController();
	};

	/**************************************
	GlassShardsクラス
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