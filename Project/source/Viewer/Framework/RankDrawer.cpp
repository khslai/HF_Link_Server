//=============================================================================
//
// �����L���O�`��N���X [RankDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../../main.h"
#include "RankDrawer.h"
#include "TextureDrawer.h"

#include "../../../Framework/String/String.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Math/Easing.h"

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************
const int NameDigitalMax = 3;
const int DigitalMax = 16;
const float DigitalInterval = 70.0f;
const float CharInterval = 100.0f;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
RankDrawer::RankDrawer(string Name, string AILevelStr) :
	RankNum(0),
	InScreen(true),
	AILevelStr(AILevelStr)
{
	Rank = new TextureDrawer(D3DXVECTOR2(1024.0f, 384.0f), 4, 3);
	Rank->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Ranking.png");

	PlayerName = new TextureDrawer(D3DXVECTOR2(1024.0f, 1024.0f), 6, 6);
	PlayerName->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Alphabet.png");
	PlayerName->SetSize(D3DXVECTOR2(100.0f, 100.0f));

	AILevel = new TextureDrawer(D3DXVECTOR2(512.0f, 384.0f), 4, 3);
	AILevel->LoadTexture("data/TEXTURE/Viewer/RankingViewer/Number.png");

	SetDrawPosition();
	SplitAILevel();
	SplitName(Name);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
RankDrawer::~RankDrawer()
{
	SAFE_DELETE(PlayerName);
	SAFE_DELETE(AILevel);
	SAFE_DELETE(Rank);
	SplitedLevel.clear();
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
	for (unsigned int i = 0; i < NameDigitalMax; i++)
	{
		// ��(�ő包)����`��
		PlayerName->SetPosition(NameBasePos + D3DXVECTOR3((i * CharInterval), 0.0f, 0.0f));
		PlayerName->SetIndex(SplitedName.at(i));
		PlayerName->Draw();
	}

	// AI���x���\��
	for (unsigned int i = 0; i < SplitedLevel.size(); i++)
	{
		// ��(�ő包)����`��
		AILevel->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevel->SetIndex(SplitedLevel.at(i));
		AILevel->Draw();
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
	for (unsigned int i = 0; i < NameDigitalMax; i++)
	{
		// ��(�ő包)����`��
		PlayerName->SetPosition(NameBasePos + D3DXVECTOR3((i * CharInterval), 0.0f, 0.0f));
		PlayerName->SetIndex(SplitedName.at(i));
		PlayerName->Draw();
	}

	// AI���x���\��
	for (unsigned int i = 0; i < SplitedLevel.size(); i++)
	{
		// ��(�ő包)����`��
		AILevel->SetPosition(AILevelBasePos + D3DXVECTOR3(((i + 1) * DigitalInterval), 0.0f, 0.0f));
		AILevel->SetIndex(SplitedLevel.at(i));
		AILevel->Draw();
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
	NameBasePos = CenterPos + D3DXVECTOR3(-250.0f, 0.0f, 0.0f);
	AILevelBasePos = CenterPos + D3DXVECTOR3(30.0f, 0.0f, 0.0f);
	Rank->SetPosition(CenterPos + D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
}

//=============================================================================
// AILevel�̕�����𕪊�
//=============================================================================
void RankDrawer::SplitAILevel(void)
{
	string StrTemp = AILevelStr;
	bool ZeroScore = true;

	for (int i = 0; i < DigitalMax; i++)
	{
		if (!StrTemp.empty())
		{
			// ������̍ŏ�1�������擾
			char Num = StrTemp.front();

			if (Num != '0' || !ZeroScore)
			{
				ZeroScore = false;
				// int�^�ɕϊ��A�ۑ�
				SplitedLevel.push_back(Num - '0');
			}

			// �ŏ��̐����폜
			StrTemp.erase(StrTemp.begin());
		}
		else
		{
			break;
		}
	}

	if (SplitedLevel.empty())
	{
		SplitedLevel.push_back(0);
	}
}

//=============================================================================
// �v���C���[���O�̕�����𕪊�
//=============================================================================
void RankDrawer::SplitName(string NameStr)
{
	for (int i = 0; i < NameDigitalMax; i++)
	{
		if (!NameStr.empty())
		{
			// ������̍ŏ�2�������擾
			string Num;
			Num.push_back(NameStr.front());
			NameStr.erase(NameStr.begin());
			Num.push_back(NameStr.front());
			NameStr.erase(NameStr.begin());

			// int�^�ɕϊ��A�ۑ�
			SplitedName.push_back(stoi(Num));
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

//=============================================================================
// AILevel�̕�������擾
//=============================================================================
string RankDrawer::GetAILevelStr(void)
{
	return AILevelStr;
}
