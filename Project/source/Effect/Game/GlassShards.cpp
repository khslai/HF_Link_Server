//=====================================
//
// ガラス破片エフェクト処理[GlassShards.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "GlassShards.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	GlassShardsControllerコンストラクタ
	***************************************/
	GlassShardsController::GlassShardsController() :
		BaseParticleController(Particle_2D)
		//BaseParticleController(Particle_3D)
	{
		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/GlassShards.png");

		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 200.0f, -200.0f };
		const D3DXVECTOR2 TextureDiv{ 3.0f, 2.0f };
		MakeUnitBuffer(ParticleSize, TextureDiv);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new GlassShards();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 1;
		const int NumEmit = 32;
		const int EmitDuration = 1;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, EmitDuration);
		}
	}

	/**************************************
	GlassShards statciメンバ
	***************************************/
	const int GlassShards::Life = 60;
	const int GlassShards::TexUV_U = 3;
	const int GlassShards::TexUV_V = 2;
	const float GlassShards::MinSpeed = 10.0f;
	const float GlassShards::MaxSpeed = 30.0f;

	/**************************************
	GlassShardsコンストラクタ
	***************************************/
	GlassShards::GlassShards() :
		Particle2D(Life),
		InitSpeed(MaxSpeed),
		moveDirection(Vector3::Zero)
	{
	}

	/**************************************
	GlassShards初期化処理
	***************************************/
	void GlassShards::Init()
	{
		cntFrame = 0;
		active = true;

		//スケーリング
		float scale = Math::RandomRange(0.5f, 1.0f);
		transform->SetScale(Vector3::One * scale);

		//移動方向を設定
		//moveDirection = Vector3::Random();
		moveDirection = D3DXVECTOR3(
			Math::RandomRange(-1.0f, 1.0f),
			Math::RandomRange(-1.0f, 1.0f),
			0.0f
		);

		D3DXVec3Normalize(&moveDirection, &moveDirection);
		//初期位置を移動方向へオフセット
		transform->Move(moveDirection);

		//UV座標を決定
		int indexUV = Math::RandomRange(0, TexUV_U * TexUV_V);
		uv.u = indexUV % TexUV_U / (float)TexUV_U;
		uv.v = indexUV / TexUV_U / (float)TexUV_V;
	}

	/**************************************
	GlassShards更新処理
	***************************************/
	void GlassShards::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//スピードをイージングで求めて移動計算
		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, MaxSpeed, MinSpeed, EaseType::OutQuart);
		if (cntFrame >= lifeFrame - 5)
		{
			speed = MaxSpeed * 0.8f;
		}
		transform->Move(moveDirection * speed);

		//回転
		float DegreeZ = Easing::EaseValue(t, 10.0f, 1.0f, EaseType::OutQuart);
		transform->Rotate(0.0f, 0.0f, DegreeZ);
	}
}