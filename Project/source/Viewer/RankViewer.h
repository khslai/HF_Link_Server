//=============================================================================
//
// ランキング描画クラス [RankViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _RankViewer_H_
#define _RankViewer_H_

#include <string>
#include <vector>

using namespace std;

class TextViewer;
class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RankViewer
{
private:
	// 順位
	int RankNum;
	// 画面内描画フラグ
	bool InScreen;
	// AIレベルの文字列
	string AILevelStr;
	// 描画の中心座標
	D3DXVECTOR3 CenterPos;
	// 移動先座標
	D3DXVECTOR3 DestPos;
	// AIレベル描画の基準座標
	D3DXVECTOR3 AILevelBasePos;
	// 分割したAIレベル
	std::vector<int> SplitedInt;
	// プレイヤーの名前表示
	TextViewer *PlayerName;
	// AIレベル表示
	TextureDrawer *AILevelDrawer;
	// 順位表示
	TextureDrawer *RankDrawer;

	// テキストとテクスチャの描画位置を設定
	void SetDrawPosition(void);
	// AILevelの文字列を分割
	void SplitAILevel(void);

public:
	RankViewer(string Name, string AILevelStr);
	~RankViewer();
	void Update(void);
	void Draw(void);
	void CreateRankTexture(LPDIRECT3DTEXTURE9* Texture);
	void SetPosition(D3DXVECTOR3 Pos);
	void SetRankNum(int RankNum) { this->RankNum = RankNum; };
	D3DXVECTOR3 GetPosition(void) { return this->CenterPos; };
	unsigned long long GetAILevel(void);
};

#endif
