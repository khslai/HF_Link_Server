//=====================================
//
// ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "GameParticleManager.h"
#include "../../Framework/PostEffect/CrossFilterController.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "Game/ExpandEffect.h"
#include "Game/BlueDebris.h"
#include "Game/GlassShards.h"
#include "Game/GlassBroken.h"
#include "Game/ColorfulDebris.h"

/**************************************
staticメンバ
***************************************/


/**************************************
初期化処理
***************************************/
void GameParticleManager::Init()
{
	SceneParticleManager::Init();

	controllers.resize(GameParticle::Max, NULL);
	controllers[GameParticle::ExpandEffect] = new Effect::Game::ExpandEffectController();
	controllers[GameParticle::BlueDebris] = new Effect::Game::BlueDebrisController();
	controllers[GameParticle::GlassShards] = new Effect::Game::GlassShardsController();
	controllers[GameParticle::GlassBroken] = new Effect::Game::GlassBrokenController();
	controllers[GameParticle::ColorfulDebris] = new Effect::Game::ColorfulDebrisController();
}

/**************************************
描画処理
***************************************/
void GameParticleManager::Draw3DParticle()
{
#if _DEBUG
	Debug::Begin("Effect Test");
	if (Debug::Button("ColorfulDebris"))
	{
		SetColorfulDebris(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
	}
	Debug::End();
#endif

	SceneParticleManager::Draw3DParticle();
}

/**************************************
描画処理
***************************************/
void GameParticleManager::Draw2DParticle()
{
	SceneParticleManager::Draw2DParticle();
}

/**************************************
ランキング展開のエフェクトセット処理
***************************************/
void GameParticleManager::SetExpandEffect(D3DXVECTOR3 Pos, std::function<void(void)> callback)
{
	controllers[GameParticle::ExpandEffect]->SetEmitter(Pos, nullptr);
}

/**************************************
青い粒子エフェクトセット処理
***************************************/
void GameParticleManager::SetBlueDebris(D3DXVECTOR3 Pos, std::function<void(void)> callback)
{
	controllers[GameParticle::BlueDebris]->SetEmitter(Pos, nullptr);
}

/**************************************
ガラス破片エフェクトセット処理
***************************************/
void GameParticleManager::SetGlassShards(void)
{
	controllers[GameParticle::GlassShards]->SetEmitter(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), nullptr);
	controllers[GameParticle::GlassBroken]->SetEmitter(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), nullptr);
}

/**************************************
カラー粒子エフェクトセット処理
***************************************/
void GameParticleManager::SetColorfulDebris(D3DXVECTOR3 Pos, std::function<void(void)> callback)
{
	controllers[GameParticle::ColorfulDebris]->SetEmitter(Pos, nullptr);
}

