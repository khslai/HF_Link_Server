//=============================================================================
//
// �����L���O�`��N���X [RankDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _RankDrawer_H_
#define _RankDrawer_H_

#include <string>
#include <vector>

using namespace std;

class TextViewer;
class SplitTextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RankDrawer
{
private:
	// ����
	int RankNum;
	// ��ʓ��`��t���O
	bool InScreen;
	// AI���x���̕�����
	string AILevelStr;
	// �`��̒��S���W
	D3DXVECTOR3 CenterPos;
	// �ړ�����W
	D3DXVECTOR3 DestPos;
	// AI���x���`��̊���W
	D3DXVECTOR3 AILevelBasePos;
	// ��������AI���x��
	std::vector<int> SplitedInt;
	// �v���C���[�̖��O�\��
	TextViewer *PlayerName;
	// AI���x���\��
	SplitTextureDrawer *AILevelDrawer;
	// ���ʕ\��
	SplitTextureDrawer *Rank;

	// �e�L�X�g�ƃe�N�X�`���̕`��ʒu��ݒ�
	void SetDrawPosition(void);
	// AILevel�̕�����𕪊�
	void SplitAILevel(void);

public:
	RankDrawer(string Name, string AILevelStr);
	~RankDrawer();
	void Update(void);
	void Draw(void);
	void CreateRankTexture(LPDIRECT3DTEXTURE9* Texture);
	void SetPosition(D3DXVECTOR3 Pos);
	void SetRankNum(int RankNum) { this->RankNum = RankNum; };
	D3DXVECTOR3 GetPosition(void) { return this->CenterPos; };
	unsigned long long GetAILevel(void);
};

#endif
