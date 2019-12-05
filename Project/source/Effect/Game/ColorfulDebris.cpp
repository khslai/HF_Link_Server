//=====================================
//
// カラー粒子エフェクト処理[ColorfulDebris.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "ColorfulDebris.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	コンストラクタ
	***************************************/
	ColorfulDebrisController::ColorfulDebrisController() :
		BaseParticleController(Particle_2D)
	{
		//単位頂点バッファ作成
		const D3DXVECTOR2 SizeParticle = { 30.0f, -30.0f };
		const D3DXVECTOR2 DivParticle = { 4.0f, 4.0f };
		MakeUnitBuffer(SizeParticle, DivParticle);

		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/levelup.png");

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new ColorfulDebris();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 16;
		const int DurationEmit = 1;
		const int NumEmit = 30;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	ColorfulDebrisコンストラクタ
	***************************************/
	const int ColorfulDebris::Life = 60;

	/**************************************
	ColorfulDebrisコンストラクタ
	***************************************/
	ColorfulDebris::ColorfulDebris() :
		Particle2D(Life),
		speed(Math::RandomRange(5.0f, 15.0f))
		//initScale(Math::RandomRange(1.0f))
		//directionMove(Vector3::Down)
	{
	}

	/**************************************
	ColorfulDebrisデストラクタ
	***************************************/
	ColorfulDebris::~ColorfulDebris()
	{
	}

	/**************************************
	ColorfulDebris初期化処理
	***************************************/
	void ColorfulDebris::Init()
	{
		cntFrame = 0;
		active = true;

		int randomIndex = Math::RandomRange(0, 16);
		uv.u = randomIndex % 4 / 4.0f;
		uv.v = randomIndex / 4 / 4.0f;

		D3DXVECTOR3 BasePos = transform->GetPosition();
		float Length = Math::RandomRange(0.0f, 100.0f);
		D3DXVECTOR3 position = BasePos + D3DXVECTOR3{
			cosf(D3DXToRadian(Math::RandomRange(0.0f,360.0f))) * Length,
			sinf(D3DXToRadian(Math::RandomRange(0.0f,360.0f))) * Length,
			0.0f
		};
		position.z = 0.0f;
		transform->SetPosition(position);
	}

	/**************************************
	ColorfulDebris更新処理
	***************************************/
	void ColorfulDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		// 2DのY軸と3DのY軸は逆
		transform->Move(Vector3::Up * speed);
		//transform->Rotate(0.0f, 0.0f, 30.0f);
	}
}