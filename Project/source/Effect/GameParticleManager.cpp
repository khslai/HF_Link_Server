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
}

/**************************************
描画処理
***************************************/
void GameParticleManager::Draw()
{
	SceneParticleManager::Draw();
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
