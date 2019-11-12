//=============================================================================
//
// UDPサーバー描画クラス [UDPServerViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../main.h"
#include "UDPServerViewer.h"
#include "../Framework/Renderer2D/TextViewer.h"
#include "../Framework/String/String.h"
#include "../Framework/Tool/DebugWindow.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
UDPServerViewer::UDPServerViewer()
{
	TitleText = new TextViewer("data/TEXTURE/Viewer/EventViewer/EventMessage/Text_cinecaption226.ttf", 80);
	TitleText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	TitleText->SetPos((int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 10 * 2.0f));
	TitleText->SetText("ランキング表示");
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{

}

//=============================================================================
// 更新
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
// 描画
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
// 受信スレッド(マルチスレッド用)
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
// 受け取ったメッセージを処理
//=============================================================================
void UDPServerViewer::SetMessage(const char * Message, sockaddr_in Address)
{
	for (auto &Drawer : DrawList)
	{
		if (Drawer.Address.sin_port == Address.sin_port &&
			strcmp(inet_ntoa(Drawer.Address.sin_addr), inet_ntoa(Address.sin_addr)) == 0)
		{
			char Text[256];
			sprintf(Text, "送信元IP/Port：%s/%d\n%s",
				inet_ntoa(Drawer.Address.sin_addr), 
				ntohs(Drawer.Address.sin_port),
				Message);
			Drawer.Text->SetText(Text);
		}
	}
}

//=============================================================================
// 受け取ったメッセージを処理
//=============================================================================
void UDPServerViewer::SetMessage(std::vector<string> SplitedStr, sockaddr_in Address)
{
	for (auto &Drawer : DrawList)
	{
		if (Drawer.Address.sin_port == Address.sin_port &&
			strcmp(inet_ntoa(Drawer.Address.sin_addr), inet_ntoa(Address.sin_addr)) == 0)
		{
			char Text[256];
			sprintf(Text, "プレイヤーの名前：%s\nAIレベル：%s",
				SplitedStr.at(0).c_str(),
				SplitedStr.at(1).c_str());
			Drawer.Text->SetText(Text);
		}
	}
}

