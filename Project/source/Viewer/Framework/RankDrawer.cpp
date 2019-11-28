//=============================================================================
//
// �����L���O�`��N���X [RankDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "RankDrawer.h"
#include "SplitTextureDrawer.h"

#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/String/String.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Math/Easing.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
const int DigitalMax = 16;
const float DigitalInterval = 70.0f;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
RankDrawer::RankDrawer(string Name, string AILevelStr) :
	RankNum(0),
	InScreen(true),
	AILevelStr(AILevelStr)
{
	Rank = new SplitTextureDrawer(4, 3, D3DXVECTOR2(1024.0f, 384.0f));
	Rank->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Ranking.png");

	PlayerName = new TextViewer("data/TEXTURE/Viewer/RankingViewer/Text_cinecaption226.ttf", 80);
	PlayerName->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	PlayerName->SetText(Name);

	AILevelDrawer = new SplitTextureDrawer(4, 3, D3DXVECTOR2(512.0f, 384.0f));
	AILevelDrawer->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Number.png");

	SetDrawPosition();
	SplitAILevel();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
RankDrawer::~RankDrawer()
{
	SAFE_DELETE(PlayerName);
	SAFE_DELETE(AILevelDrawer);
	SAFE_DELETE(Rank);
	SplitedInt.clear();
}

//=============================================================================
// �X�V
//=============================================================================
void RankDrawer::Update(void)
{
}

//=============================================================================
// �`��
//=============================================================================
void RankDrawer::Draw(void)
{
	// ��ʊO��������A�`�悵�Ȃ�
	if (!InScreen)
		return;

	// ���ʕ\��
	Rank->SetIndex(RankNum);
	Rank->Draw();

	// �v���C���[�̖��O�\��
	PlayerName->Draw();

	// AI���x���\��
	for (unsigned int i = 0; i < SplitedInt.size(); i++)
	{
		// ��(�ő包)����`��
		AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetIndex(SplitedInt.at(i));
		AILevelDrawer->Draw();
	}
}

//=============================================================================
// �W�J�p�̃e�N�X�`�������
//=============================================================================
void RankDrawer::CreateRankTexture(LPDIRECT3DTEXTURE9* Texture)
{
	LPDIRECT3DSURFACE9 OldSurface;
	LPDIRECT3DSURFACE9 RenderSurface;
	LPDIRECT3DTEXTURE9 RenderTexture;
	LPDIRECT3DDEVICE9 Device = GetDevice();
	const D3DXCOLOR BackColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	const D3DXVECTOR3 DrawPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 60.0f, 0.0f);
	SetPosition(DrawPos);

	//�����_�[�e�N�X�`���쐬
	Device->CreateTexture(SCREEN_WIDTH, 120,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&RenderTexture,
		0);

	RenderTexture->GetSurfaceLevel(0, &RenderSurface);

	//�����_�[�^�[�Q�b�g�؂�ւ�
	Device->GetRenderTarget(0, &OldSurface);
	Device->SetRenderTarget(0, RenderSurface);
	Device->Clear(0, NULL, D3DCLEAR_TARGET, BackColor, 1.0f, 0);

	// ���ʕ\��
	Rank->SetIndex(RankNum);
	Rank->Draw();

	// �v���C���[�̖��O�\��
	PlayerName->Draw();

	// AI���x���\��
	for (unsigned int i = 0; i < SplitedInt.size(); i++)
	{
		// ��(�ő包)����`��
		AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetIndex(SplitedInt.at(i));
		AILevelDrawer->Draw();
	}

	//�����_�[�^�[�Q�b�g����
	Device->SetRenderTarget(0, OldSurface);
	SAFE_RELEASE(OldSurface);
	SAFE_RELEASE(RenderSurface);

	*Texture = RenderTexture;
	RenderTexture = nullptr;
}

//=============================================================================
// �e�L�X�g�ƃe�N�X�`���̕`��ʒu��ݒ�
//=============================================================================
void RankDrawer::SetPosition(D3DXVECTOR3 Pos)
{
	CenterPos = Pos;
	InScreen = CenterPos.y > (SCREEN_HEIGHT - 60.0f) ? false : true;
	SetDrawPosition();
}

//=============================================================================
// �e�L�X�g�ƃe�N�X�`���̕`��ʒu��ݒ�
//=============================================================================
void RankDrawer::SetDrawPosition(void)
{
	PlayerName->SetPos((int)(CenterPos.x - 150), (int)(CenterPos.y));
	AILevelBasePos = CenterPos + D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	Rank->SetPosition(CenterPos + D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
}

//=============================================================================
// AILevel�̕�����𕪊�
//=============================================================================
void RankDrawer::SplitAILevel(void)
{
	string StrTemp = AILevelStr;

	for (int i = 0; i < DigitalMax; i++)
	{
		if (!StrTemp.empty())
		{
			// ������̍ŏ�1�������擾
			char Num = StrTemp.front();

			// int�^�ɕϊ��A�ۑ�
			SplitedInt.push_back(Num - '0');

			// �ŏ��̐����폜
			StrTemp.erase(StrTemp.begin());
		}
		else
		{
			break;
		}
	}
}

//=============================================================================
// AILevel�̕������unsinged long long�^�ɕϊ�
//=============================================================================
unsigned long long RankDrawer::GetAILevel(void)
{
	return std::strtoull(AILevelStr.c_str(), NULL, 10);
}