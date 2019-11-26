//=====================================
//
// ランキング展開エフェクト処理[ExpandEffect.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "ExpandEffect.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	コンストラクタ
	***************************************/
	ExpandEffectController::ExpandEffectController() :
		BaseParticleController(Particle_2D)
	{
		//単位頂点バッファ作成
		//スクリーン座標で扱うのでYサイズをマイナスにすることに注意
		const D3DXVECTOR2 SizeParticle{ 50.0f, -50.0f };
		MakeUnitBuffer(SizeParticle);

		//テクスチャ読み込み
		const char* Path = "data/TEXTURE/Particle/MoveTail.png";
		LoadTexture(Path);

		//パーティクルコンテナ作成
		const int MaxParticle = 32;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new ExpandEffect();
		}

		//エミッタコンテナ作成
		const int MaxEmitter = 2;
		const int NumEmit = 32;
		const int DurationEmit = 60;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, DurationEmit);
		}
	}

	/**************************************
	描画
	***************************************/
	//bool ExpandEffectController::Draw(void)
	//{
	//	bool Result = false;
	//	LPDIRECT3DDEVICE9 Device = GetDevice();

	//	//レンダーステートを加算合成に設定
	//	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	Result = BaseParticleController::Draw();

	//	//レンダーステートを元に戻す
	//	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//	return Result;
	//}

	/**************************************
	ExpandEffectコンストラクタ
	***************************************/
	const int ExpandEffect::Life = 60;

	/**************************************
	ExpandEffectコンストラクタ
	***************************************/
	ExpandEffect::ExpandEffect() :
		Particle2D(Life)
	{
	}

	/**************************************
	ExpandEffectデストラクタ
	***************************************/
	ExpandEffect::~ExpandEffect()
	{
	}

	/**************************************
	ExpandEffect初期化処理
	***************************************/
	void ExpandEffect::Init()
	{
		cntFrame = 0;
		active = true;

		D3DXVECTOR3 BasePos = transform->GetPosition();
		D3DXVECTOR3 position{
			BasePos.x,
			BasePos.y + Math::RandomRange(-60.0f, 60.0f),
			0.0f
		};
		transform->SetPosition(position);
	}

	/**************************************
	ExpandEffect更新処理
	***************************************/
	void ExpandEffect::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		float t = (float)cntFrame / lifeFrame;

		D3DXVECTOR3 Pos = transform->GetPosition();
		Pos.x = Easing::EaseValue(t, 0.0f, (float)SCREEN_WIDTH, EaseType::InQuart);
		transform->SetPosition(Pos);
	}
}