//=====================================
//
// 青い粒子エフェクト処理[BlueDebris.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "BlueDebris.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	BlueDebrisControllerコンストラクタ
	***************************************/
	BlueDebrisController::BlueDebrisController() :
		BaseParticleController(Particle_3D)
	{
		//テクスチャ読み込み
		LoadTexture("data/TEXTURE/Particle/blueDebris.png");

		//単位頂点バッファ作成
		const D3DXVECTOR2 ParticleSize{ 1.0f, 1.0f };
		const D3DXVECTOR2 TextureDiv{ (float)BlueDebris::TexDiv, (float)BlueDebris::TexDiv };
		MakeUnitBuffer(ParticleSize, TextureDiv);

		//パーティクルコンテナ作成
		const unsigned MaxParticle = 256;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new BlueDebris();
		}

		//エミッターコンテナ作成
		const unsigned MaxEmitter = 1;
		const int NumEmit = 1;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(NumEmit, true);
		}
	}

	/**************************************
	BlueDebris statciメンバ
	***************************************/
	const int BlueDebris::MinLife = 60;
	const int BlueDebris::MaxLife = 120;
	const float BlueDebris::MinSpeed = 0.05f;
	const float BlueDebris::MaxSpeed = 0.2f;
	const int BlueDebris::TexDiv = 3;

	/**************************************
	BlueDebrisコンストラクタ
	***************************************/
	BlueDebris::BlueDebris() :
		Particle3D(MinLife, MaxLife),
		InitSpeed(Math::RandomRange(MinSpeed, MaxSpeed)),
		moveDirection(Vector3::Zero)
	{
	}

	/**************************************
	BlueDebris初期化処理
	***************************************/
	void BlueDebris::Init()
	{
		cntFrame = 0;
		active = true;

		//スケーリング
		float scale = Math::RandomRange(0.2f, 1.2f);
		transform->SetScale(Vector3::One * scale);

		//移動方向を設定
		//moveDirection = Vector3::Random();
		moveDirection = D3DXVECTOR3(
			Math::RandomRange(-0.5f, 0.5f),
			Math::RandomRange(-0.5f, 0.5f),
			Math::RandomRange(0.0f, -1.0f)
		);

		D3DXVec3Normalize(&moveDirection, &moveDirection);

		//UV座標を決定
		int indexUV = Math::RandomRange(0, TexDiv * TexDiv);
		uv.u = indexUV % TexDiv / (float)TexDiv;
		uv.v = indexUV / TexDiv / (float)TexDiv;

		//初期位置を移動方向へオフセット
		transform->Move(moveDirection);
	}

	/**************************************
	BlueDebris更新処理
	***************************************/
	void BlueDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame++;

		//スピードをイージングで求めて移動計算
		float t = (float)cntFrame / lifeFrame;
		float speed = Easing::EaseValue(t, InitSpeed, MaxSpeed, EaseType::Linear);
		transform->Move(moveDirection * speed);

		//スケール計算
		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::Linear);
		transform->SetScale(Vector3::One * scale);

		//回転
		const float angleRotate = 10.0f;
		transform->Rotate(0.0f, 0.0f, angleRotate);
	}

}