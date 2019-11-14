//=============================================================================
//
// �����L���O�`��N���X [RankViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "RankViewer.h"
#include "TextureDrawer.h"

#include "../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
const int DigitalMax = 16;
const float DigitalInterval = 70.0f;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
RankViewer::RankViewer(string Name, string AILevelStr) :
	AILevelStr(AILevelStr)
{
	PlayerName = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 80);
	PlayerName->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	PlayerName->SetText(Name);

	AILevelDrawer = new TextureDrawer(4, 3, D3DXVECTOR2(512.0f, 384.0f));
	AILevelDrawer->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Number.png");

	RankDrawer = new TextureDrawer(4, 3, D3DXVECTOR2(1024.0f, 384.0f));
	RankDrawer->LoadTexture("data/TEXTURE/Viewer/GameViewer/LevelViewer/Ranking.png");

	SetDrawPosition();
	SplitAILevel();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
RankViewer::~RankViewer()
{
	SAFE_DELETE(PlayerName);
	SAFE_DELETE(AILevelDrawer);
	SAFE_DELETE(RankDrawer);
	SplitedInt.clear();
}

//=============================================================================
// �X�V
//=============================================================================
void RankViewer::Update(void)
{
}

//=============================================================================
// �`��
//=============================================================================
void RankViewer::Draw(void)
{
	// �v���C���[�̖��O�\��
	PlayerName->Draw();

	//for (int i = 0; i < DigitalMax; i++)
	for (unsigned int i = 0; i < SplitedInt.size(); i++)
	{
		// ��(�ő包)����`��
		//AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((DigitalMax - i) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetTexture(SplitedInt.at(i));
		AILevelDrawer->Draw();
	}

	RankDrawer->SetTexture(RankNum);
	RankDrawer->Draw();
}

//=============================================================================
// �e�L�X�g�ƃe�N�X�`���̕`��ʒu��ݒ�
//=============================================================================
void RankViewer::SetPosition(D3DXVECTOR3 Pos)
{
	CenterPos = Pos;
	SetDrawPosition();
}

//=============================================================================
// �e�L�X�g�ƃe�N�X�`���̕`��ʒu��ݒ�
//=============================================================================
void RankViewer::SetDrawPosition(void)
{
	PlayerName->SetPos((int)(CenterPos.x - 200), (int)(CenterPos.y));
	AILevelBasePos = CenterPos + D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	RankDrawer->SetPosition(CenterPos + D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
}

//=============================================================================
// AILevel�̕�����𕪊�
//=============================================================================
void RankViewer::SplitAILevel(void)
{
	string StrTemp = AILevelStr;

	for (int i = 0; i < DigitalMax; i++)
	{
		if (!StrTemp.empty())
		{
			// ������̍ŏ��ꌅ���擾
			char Num = StrTemp.front();

			// int�^�ɕϊ��A�ۑ�
			SplitedInt.push_back(Num - '0');

			// �ŏ��̐����폜
			StrTemp.erase(StrTemp.begin());
		}
		else
		{
			break;
			//SplitedInt.push_back(0);
		}
	}
}

//=============================================================================
// AILevel�̕������unsinged long long�^�ɕϊ�
//=============================================================================
unsigned long long RankViewer::GetAILevel(void)
{
	return std::strtoull(AILevelStr.c_str(), NULL, 10);
}