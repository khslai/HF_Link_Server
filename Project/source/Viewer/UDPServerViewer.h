//=============================================================================
//
// UDP�T�[�o�[�`��N���X [UDPServerViewer.h]
// Author : HAL���� GP12B332 41 ���M��
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
// �N���X��`
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
