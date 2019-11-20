//=============================================================================
//
// UDPサーバー描画クラス [UDPServerViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _UDPServerViewer_H_
#define _UDPServerViewer_H_

#include <string>
#include <vector>

using namespace std;

class RankViewer;
class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPServerViewer
{
private:
	int CountFrame;
	int InsertNum;
	int State;								// 状態
	TextureDrawer *RankingTitle;			// タイトル
	TextureDrawer *ExpandTexture;			// ランク追加時に演出用のテクスチャ
	RankViewer* InsertTemp;					// 追加予定のランキングビューア
	std::vector<RankViewer*> Ranking;		// ランキング
	std::vector<RankViewer*> InsertStack;	// 追加予定のスタック

	void SortRanking(RankViewer* Rank);
	void RankingMoveStart(int Num);
	void RankingExpand();
	void RankingInsert(void);

public:
	UDPServerViewer();
	~UDPServerViewer();
	void Update(void);
	void Draw(void);
	void CreateRankViewer(string PlayerName, string AILevel);
#if _DEBUG
	void ClearRanking(void);
#endif
};

#endif
