//=============================================================================
//
// ランキング描画クラス [RankDrawer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _RankDrawer_H_
#define _RankDrawer_H_

#include <string>
#include <vector>

using namespace std;

class TextViewer;
class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RankDrawer
{
private:
	
	int RankNum;					// 順位
	bool InScreen;					// 画面内描画フラグ
	string AILevelStr;				// AIレベルの文字列
	D3DXVECTOR3 CenterPos;			// 描画の中心座標
	D3DXVECTOR3 StartPos;			// 移動前の座標
	D3DXVECTOR3 AILevelBasePos;		// AIレベル描画の基準座標
	D3DXVECTOR3 NameBasePos;		// AIレベル描画の基準座標
	std::vector<int> SplitedLevel;	// 分割したAIレベル
	std::vector<int> SplitedName;	// 分割した名前
	TextureDrawer *PlayerName;		// プレイヤーの名前表示
	TextureDrawer *AILevel;			// AIレベル表示
	TextureDrawer *Rank;			// 順位表示

	// テキストとテクスチャの描画位置を設定
	void SetDrawPosition(void);
	// AILevelの文字列を分割
	void SplitAILevel(void);
	// プレイヤー名前の文字列を分割
	void SplitName(string NameStr);

public:
	RankDrawer(string Name, string AILevelStr);
	~RankDrawer();
	void Update(void);
	void Draw(void);
	void CreateRankTexture(LPDIRECT3DTEXTURE9* Texture);
	void SetPosition(D3DXVECTOR3 Pos);
	void SetStartPos(D3DXVECTOR3 Pos) { this->StartPos = Pos; };
	void SetRankNum(int RankNum) { this->RankNum = RankNum; };
	D3DXVECTOR3 GetPosition(void) { return this->CenterPos; };
	D3DXVECTOR3 GetStartPos(void) { return this->StartPos; };
	unsigned long long GetAILevel(void);
	string GetAILevelStr(void);
};

#endif
