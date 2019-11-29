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
class TextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class RankDrawer
{
private:
	
	int RankNum;					// ����
	bool InScreen;					// ��ʓ��`��t���O
	string AILevelStr;				// AI���x���̕�����
	D3DXVECTOR3 CenterPos;			// �`��̒��S���W
	D3DXVECTOR3 StartPos;			// �ړ��O�̍��W
	D3DXVECTOR3 AILevelBasePos;		// AI���x���`��̊���W
	D3DXVECTOR3 NameBasePos;		// AI���x���`��̊���W
	std::vector<int> SplitedLevel;	// ��������AI���x��
	std::vector<int> SplitedName;	// �����������O
	TextureDrawer *PlayerName;		// �v���C���[�̖��O�\��
	TextureDrawer *AILevel;			// AI���x���\��
	TextureDrawer *Rank;			// ���ʕ\��

	// �e�L�X�g�ƃe�N�X�`���̕`��ʒu��ݒ�
	void SetDrawPosition(void);
	// AILevel�̕�����𕪊�
	void SplitAILevel(void);
	// �v���C���[���O�̕�����𕪊�
	void SplitName(string NameStr);

public:
	RankDrawer(string Name, string AILevelStr);
	~RankDrawer();
	void Update(void);
	void Draw(void);
	void CreateRankTexture(LPDIRECT3DTEXTURE9* Texture);
	void SetPosition(D3DXVECTOR3 Pos);
	void SetStartPos(D3DXVECTOR3 Pos) { this->StartPos = Pos; };
	void SetRankNum(int RankNum) { this->RankNum = RankNum; };
	D3DXVECTOR3 GetPosition(void) { return this->CenterPos; };
	D3DXVECTOR3 GetStartPos(void) { return this->StartPos; };
	unsigned long long GetAILevel(void);
	string GetAILevelStr(void);
};

#endif
