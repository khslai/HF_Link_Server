//=============================================================================
//
// ゲームパーティクルマネージャ処理[GameParticleManager.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _GAMEPARTICLEMANAGER_H_
#define _GAMEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
ゲームシーンのパーティクル通し番号
***************************************/
namespace GameParticle
{
	enum ID
	{
		ExpandEffect,		// ランキング展開のエフェクト
		BlueDebris,			// 青い粒子
		GlassShards,		// ガラス破片
		GlassBroken,		// スクリーン割れる
		Max
	};
}

/**************************************
クラス定義
***************************************/
class GameParticleManager : public SceneParticleManager, public BaseSingleton<GameParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	//初期化処理
	void Init() override;

	//描画処理
	void Draw3DParticle() override;
	void Draw2DParticle() override;

	// ランキング展開のエフェクトセット処理
	void SetExpandEffect(D3DXVECTOR3 Pos, std::function<void(void)> callback = nullptr);
	// 青い粒子エフェクトセット処理
	void SetBlueDebris(D3DXVECTOR3 Pos, std::function<void(void)> callback = nullptr);
	// ガラス破片エフェクトセット処理
	void SetGlassShards(D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f,0.0f,0.0f), std::function<void(void)> callback = nullptr);


};

#endif