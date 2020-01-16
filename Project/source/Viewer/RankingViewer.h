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
	int ChangeAnimInterval;
	int InsertNum;
	int State;								// ���
	bool EventHappened;						// �C�x���g�����������t���O
	TextureDrawer *RankingTitle;			// �^�C�g��
	TextureDrawer *ExpandTexture;			// �����N�ǉ����ɉ��o�p�̃e�N�X�`��
	RankDrawer* InsertTemp;					// �ǉ��\��̃����L���O�r���[�A
	std::vector<RankDrawer*> Ranking;		// �����L���O
	std::vector<RankDrawer*> InsertStack;	// �ǉ��\��̃X�^�b�N
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
