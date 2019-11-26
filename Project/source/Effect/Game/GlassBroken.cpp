//=====================================
//
// スクリーン割れるエフェクト処理[GlassBroken.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "GlassBroken.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	コンストラクタ
	***************************************/
	GlassBrokenController::GlassBrokenController() :
		BaseParticleController(Particle_2D)
	{
		//単位頂点バッファ作成
		//スクリーン座標で扱うのでYサイズをマイナスにすることに注意
		const D3DXVECTOR2 SizeParticle{ 1920.0f, -1080.0f};
		MakeUnitBuffer(SizeParticle);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/GlassBroken.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const int MaxParticle = 1;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new GlassBroken();
		}

		//エミッタコンテナ作成
		const int MaxEmitter = 1;
		const int NumEmit = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit);
		}
	}

	/**************************************
	GlassBrokenコンストラクタ
	***************************************/
	const int GlassBroken::Life = 60;

	/**************************************
	GlassBrokenコンストラクタ
	***************************************/
	GlassBroken::GlassBroken() :
		Particle2D(Life)
	{
	}

	/**************************************
	GlassBrokenデストラクタ
	***************************************/
	GlassBroken::~GlassBroken()
	{
	}

	/**************************************
	GlassBroken初期化処理
	***************************************/
	void GlassBroken::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	GlassBroken更新処理
	***************************************/
	void GlassBroken::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;
	}
}