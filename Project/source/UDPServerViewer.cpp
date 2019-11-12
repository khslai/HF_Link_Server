//=============================================================================
//
// UDP�T�[�o�[�`��N���X [UDPServerViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../main.h"
#include "UDPServerViewer.h"
#include "../Framework/Renderer2D/TextViewer.h"
#include "../Framework/String/String.h"
#include "../Framework/Tool/DebugWindow.h"

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
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{

}

//=============================================================================
// �X�V
//=============================================================================
void UDPServerViewer::Update(void)
{
	SAFE_DELETE(TitleText);

	for (auto &Drawer : DrawList)
	{
		SAFE_DELETE(Drawer.Text);
	}
	DrawList.clear();
}

//=============================================================================
// �`��
//=============================================================================
void UDPServerViewer::Draw(void)
{
	Debug::Begin("UDP Server's Clients");
	for (auto &Drawer : DrawList)
	{
		Debug::Text("IP Address:%s", inet_ntoa(Drawer.Address.sin_addr));
		Debug::Text("Port:%d", Drawer.Address.sin_port);
		Debug::NewLine();
	}
	Debug::End();

	TitleText->Draw();
	for (auto &Drawer : DrawList)
	{
		Drawer.Text->Draw();
	}
}

//=============================================================================
// ��M�X���b�h(�}���`�X���b�h�p)
//=============================================================================
void UDPServerViewer::PushbackViewer(sockaddr_in Address)
{
	auto Text = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 50);
	Text->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	Text->SetPos((int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 10 * 2.0f + 120.0f * (ConnectedNum + 1)));
	Text->SetText("");
	DrawList.push_back(DrawViewer{ Text,Address });
	ConnectedNum++;
}

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

