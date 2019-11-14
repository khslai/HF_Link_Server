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
class TextViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPServerViewer
{
private:
	int CountFrame;
	int InsertNum;
	float MoveDestPosY;
	// 移動中フラグ
	bool InMove;
	TextureDrawer *RankingTitle;
	RankViewer* Temp;
	std::vector<RankViewer*> Ranking;

	void SortRanking(RankViewer* Rank);
	void InsertRanking(int Num, RankViewer* Rank);

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
