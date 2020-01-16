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
	int ChangeAnimInterval;
	int InsertNum;
	int State;								// 状態
	bool EventHappened;						// イベントが発生したフラグ
	TextureDrawer *RankingTitle;			// タイトル
	TextureDrawer *ExpandTexture;			// ランク追加時に演出用のテクスチャ
	RankDrawer* InsertTemp;					// 追加予定のランキングビューア
	std::vector<RankDrawer*> Ranking;		// ランキング
	std::vector<RankDrawer*> InsertStack;	// 追加予定のスタック
	std::function<void(bool)> SetIdle;

	void SortRanking(RankDrawer* Rank);
	void RankingMoveStart(int Num);
	void RankingExpand(void);
	void RankingInsert(void);
	void SetAnimation(int state);

public:
	RankingViewer(std::function<void(bool)> setIdle);
	~RankingViewer();
	void Update(void) override;
	void Draw(void) override;
	void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) override;
	void CreateViewerTex(LPDIRECT3DTEXTURE9* TexturePtr);
	void RankingRecovery(void);
	string GetLastScore(void);
	void SetEventHappened(bool Flag) { this->EventHappened = Flag; };

#if _DEBUG
	void ClearRanking(void);
#endif
};

#endif
