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
	std::function<void(bool)> SetIdle;

	void SortRanking(RankDrawer* Rank);
	void RankingMoveStart(int Num);
	void RankingExpand();
	void RankingInsert(void);

public:
	RankingViewer(std::function<void(bool)> setIdle);
	~RankingViewer();
	bool Update(void) override;
	void Draw(void) override;
	void CreateRankDrawer(string PlayerName, string AILevel);
	void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) override;
	void CreateViewerTex(LPDIRECT3DTEXTURE9* TexturePtr) override;
	void RankingRecovery(void) override;
#if _DEBUG
	void ClearRanking(void);
#endif
};

#endif
