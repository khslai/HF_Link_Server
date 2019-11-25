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
#include "BaseViewer.h"

using namespace std;

class RankViewer;
class TextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServerViewer : public BaseViewer
{
private:
	int CountFrame;
	int InsertNum;
	int State;								// ���
	TextureDrawer *RankingTitle;			// �^�C�g��
	TextureDrawer *ExpandTexture;			// �����N�ǉ����ɉ��o�p�̃e�N�X�`��
	RankViewer* InsertTemp;					// �ǉ��\��̃����L���O�r���[�A
	std::vector<RankViewer*> Ranking;		// �����L���O
	std::vector<RankViewer*> InsertStack;	// �ǉ��\��̃X�^�b�N

	void SortRanking(RankViewer* Rank);
	void RankingMoveStart(int Num);
	void RankingExpand();
	void RankingInsert(void);

public:
	UDPServerViewer();
	~UDPServerViewer();
	void Update(void) override;
	void Draw(void) override;
	void CreateRankViewer(string PlayerName, string AILevel);
	void ReceivePacket(int PacketType, const std::vector<string>& SpliteStr);

#if _DEBUG
	void ClearRanking(void);
#endif
};

#endif
