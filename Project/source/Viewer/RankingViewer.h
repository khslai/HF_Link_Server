//=============================================================================
//
// �����L���O�r���[�A�N���X [RankingViewer.h]
// Author : HAL���� GP12B332 41 ���M��
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
// �N���X��`
//*****************************************************************************
class RankingViewer : public BaseViewer
{
private:
	int CountFrame;
	int InsertNum;
	int State;								// ���
	TextureDrawer *RankingTitle;			// �^�C�g��
	TextureDrawer *ExpandTexture;			// �����N�ǉ����ɉ��o�p�̃e�N�X�`��
	RankDrawer* InsertTemp;					// �ǉ��\��̃����L���O�r���[�A
	std::vector<RankDrawer*> Ranking;		// �����L���O
	std::vector<RankDrawer*> InsertStack;	// �ǉ��\��̃X�^�b�N
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
