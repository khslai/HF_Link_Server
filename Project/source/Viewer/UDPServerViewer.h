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
class RankingMask;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServerViewer
{
private:
	int CountFrame;
	int InsertNum;
	int State;		// ���
	//float MoveDestPosY;
	// �ړ����t���O
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
