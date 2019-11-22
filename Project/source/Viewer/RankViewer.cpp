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
#include "../../Framework/Math/Easing.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
const int DigitalMax = 16;
const float DigitalInterval = 70.0f;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
RankViewer::RankViewer(string Name, string AILevelStr) :
	RankNum(0),
	InScreen(true),
	AILevelStr(AILevelStr)
{
	RankDrawer = new TextureDrawer(4, 3, D3DXVECTOR2(1024.0f, 384.0f));
	RankDrawer->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Ranking.png");

	PlayerName = new TextViewer("data/TEXTURE/Viewer/RankingViewer/Text_cinecaption226.ttf", 80);
	PlayerName->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	PlayerName->SetText(Name);

	AILevelDrawer = new TextureDrawer(4, 3, D3DXVECTOR2(512.0f, 384.0f));
	AILevelDrawer->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Number.png");

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
	// ��ʊO��������A�`�悵�Ȃ�
	if (!InScreen)
		return;

	// ���ʕ\��
	RankDrawer->SetTexture(RankNum);
	RankDrawer->Draw();

	// �v���C���[�̖��O�\��
	PlayerName->Draw();

	// AI���x���\��
	//for (int i = 0; i < DigitalMax; i++)
	for (unsigned int i = 0; i < SplitedInt.size(); i++)
	{
		// ��(�ő包)����`��
		//AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((DigitalMax - i) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetTexture(SplitedInt.at(i));
		AILevelDrawer->Draw();
	}
}

//=============================================================================
// �W�J�p�̃e�N�X�`�������
//=============================================================================
void RankViewer::CreateRankTexture(LPDIRECT3DTEXTURE9* Texture)
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
	RankDrawer->SetTexture(RankNum);
	RankDrawer->Draw();

	// �v���C���[�̖��O�\��
	PlayerName->Draw();

	// AI���x���\��
	for (unsigned int i = 0; i < SplitedInt.size(); i++)
	{
		// ��(�ő包)����`��
		AILevelDrawer->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevelDrawer->SetTexture(SplitedInt.at(i));
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
void RankViewer::SetPosition(D3DXVECTOR3 Pos)
{
	CenterPos = Pos;
	InScreen = CenterPos.y > SCREEN_HEIGHT ? false : true;
	SetDrawPosition();
}

//=============================================================================
// �e�L�X�g�ƃe�N�X�`���̕`��ʒu��ݒ�
//=============================================================================
void RankViewer::SetDrawPosition(void)
{
	PlayerName->SetPos((int)(CenterPos.x - 150), (int)(CenterPos.y));
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