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

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServerViewer
{
private:
	int CountFrame;
	int InsertNum;
	int State;			// ���
	bool InUpdateRank;
	TextureDrawer *RankingTitle;		// �^�C�g��
	RankViewer* InsertTemp;				// �ǉ��\��̃I�u�W�F�N�g
	std::vector<RankViewer*> Ranking;	// �����L���O

	TextureDrawer *ExpandTexture;			// �����N�ǉ����ɉ��o�p�̃e�N�X�`��

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
