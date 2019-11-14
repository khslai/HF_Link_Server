//=============================================================================
//
// �����L���O�`��N���X [RankViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _RankViewer_H_
#define _RankViewer_H_

#include <string>
#include <vector>

using namespace std;

class TextViewer;
class TextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RankViewer
{
private:
	int AILevel;
	int RankNum;
	string AILevelStr;
	D3DXVECTOR3 CenterPos;
	D3DXVECTOR3 AILevelBasePos;
	std::vector<int> SplitedInt;

	TextViewer *PlayerName;
	TextureDrawer *AILevelDrawer;
	TextureDrawer *RankDrawer;

	void SetDrawPosition(void);
	void SplitAILevel(void);

public:
	RankViewer(string Name, string AILevelStr);
	~RankViewer();
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Pos);
	void SetRankNum(int RankNum) { this->RankNum = RankNum; };
	unsigned long long GetAILevel(void);
};

#endif
