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
	//int ConnectedNum;
	TextViewer *TitleText;
	std::vector<RankViewer*> Ranking;
	//std::vector<sockaddr_in> ConnectedList;

	void SortRanking(RankViewer* Rank);

public:
	UDPServerViewer();
	~UDPServerViewer();
	void Update(void);
	void Draw(void);
	void CreateRankViewer(std::vector<string> SplitedStr);
#if _DEBUG
	void ClearRanking(void);
#endif
};

#endif
