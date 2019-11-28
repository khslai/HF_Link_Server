//=============================================================================
//
// ランキングビューアクラス [RankingViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _RankingViewer_H_
#define _RankingViewer_H_

#include <string>
#include <vector>
#include "BaseViewer.h"

using namespace std;

class RankDrawer;
class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RankingViewer : public BaseViewer
{
private:
	int CountFrame;
	int InsertNum;
	int State;								// 状態
	TextureDrawer *RankingTitle;			// タイトル
	TextureDrawer *ExpandTexture;			// ランク追加時に演出用のテクスチャ
	RankDrawer* InsertTemp;					// 追加予定のランキングビューア
	std::vector<RankDrawer*> Ranking;		// ランキング
	std::vector<RankDrawer*> InsertStack;	// 追加予定のスタック

	void SortRanking(RankDrawer* Rank);
	void RankingMoveStart(int Num);
	void RankingExpand();
	void RankingInsert(void);

public:
	RankingViewer();
	~RankingViewer();
	void Start(void) override;
	bool Update(void) override;
	void Draw(void) override;
	void Exit(void) override;
	void CreateRankDrawer(string PlayerName, string AILevel);
	void ReceivePacket(int PacketType, const std::vector<string>& SpliteStr);
	void CreateViewerTex(LPDIRECT3DTEXTURE9* TexturePtr) override;

#if _DEBUG
	void ClearRanking(void);
#endif
};

#endif
