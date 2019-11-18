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
class RankingMask;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPServerViewer
{
private:
	int CountFrame;
	int InsertNum;
	int State;		// 状態
	//float MoveDestPosY;
	// 移動中フラグ
	bool InMove;
	TextureDrawer *RankingTitle;
	RankViewer* InsertTemp;
	//RankingMask* Mask;
	std::vector<RankViewer*> Ranking;
	TextureDrawer *RenderTexture;

	void SortRanking(RankViewer* Rank);
	void RankingMoveStart(int Num, RankViewer* Rank);
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
