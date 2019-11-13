//=============================================================================
//
// UDP�T�[�o�[�`��N���X [UDPServerViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "UDPServerViewer.h"
#include "RankViewer.h"
#include "TextureDrawer.h"
#include "../../Framework/Renderer2D/TextViewer.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"

const int RankingMaxNum = 10;

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServerViewer::UDPServerViewer()
{
	TitleText = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 80);
	TitleText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	TitleText->SetPos((int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 10 * 2.0f));
	TitleText->SetText("�����L���O�\��");

	Ranking.reserve(RankingMaxNum);
	RankViewer* Rank = new RankViewer("Test", "123455432110");
	Rank->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, (SCREEN_HEIGHT / 10 * 2.0f + 120.0f), 0.0f));
	Ranking.push_back(Rank);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(TitleText);
	Utility::DeleteContainer(Ranking);
	//ConnectedList.clear();
}

//=============================================================================
// �X�V
//=============================================================================
void UDPServerViewer::Update(void)
{
}

//=============================================================================
// �`��
//=============================================================================
void UDPServerViewer::Draw(void)
{
	//Debug::Begin("UDP Server's Clients");
	//for (auto &Client : ConnectedList)
	//{
	//	Debug::Text("IP Address:%s", inet_ntoa(Client.sin_addr));
	//	Debug::Text("Port:%d", Client.sin_port);
	//	Debug::NewLine();
	//}
	//Debug::End();

	TitleText->Draw();

	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}
}

//=============================================================================
// ��M�X���b�h(�}���`�X���b�h�p)
//=============================================================================
void UDPServerViewer::CreateRankViewer(std::vector<string> SplitedStr)
{
	// 0�� = �v���C���[�̖��O�A1�� = AI���x��
	RankViewer* Rank = new RankViewer(SplitedStr.at(0), SplitedStr.at(1));
	Ranking.push_back(Rank);
	//ConnectedNum++;
}

#if 0
//=============================================================================
// �󂯎�������b�Z�[�W������
//=============================================================================
void UDPServerViewer::SetMessage(const char * Message, sockaddr_in Address)
{
	for (auto &Drawer : DrawList)
	{
		if (Drawer.Address.sin_port == Address.sin_port &&
			strcmp(inet_ntoa(Drawer.Address.sin_addr), inet_ntoa(Address.sin_addr)) == 0)
		{
			char Text[256];
			sprintf(Text, "���M��IP/Port�F%s/%d\n%s",
				inet_ntoa(Drawer.Address.sin_addr),
				ntohs(Drawer.Address.sin_port),
				Message);
			Drawer.Text->SetText(Text);
		}
	}
}

//=============================================================================
// �󂯎�������b�Z�[�W������
//=============================================================================
void UDPServerViewer::SetMessage(std::vector<string> SplitedStr, sockaddr_in Address)
{
	for (auto &Drawer : DrawList)
	{
		if (Drawer.Address.sin_port == Address.sin_port &&
			strcmp(inet_ntoa(Drawer.Address.sin_addr), inet_ntoa(Address.sin_addr)) == 0)
		{
			char Text[256];
			sprintf(Text, "�v���C���[�̖��O�F%s\nAI���x���F%s",
				SplitedStr.at(0).c_str(),
				SplitedStr.at(1).c_str());
			Drawer.Text->SetText(Text);
}
	}
}
#endif
//=============================================================================
// �����L���O�̏��Ԃ����߂�
//=============================================================================
void UDPServerViewer::SortRanking(void)
{

}
