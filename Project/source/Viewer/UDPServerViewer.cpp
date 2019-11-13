//=============================================================================
//
// UDPサーバー描画クラス [UDPServerViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
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

	Ranking.reserve(RankingMaxNum);
	RankViewer* Rank = new RankViewer("Test", "123455432110");
	Rank->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, (SCREEN_HEIGHT / 10 * 2.0f + 120.0f), 0.0f));
	Ranking.push_back(Rank);
}

//=============================================================================
// デストラクタ
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(TitleText);
	Utility::DeleteContainer(Ranking);
	//ConnectedList.clear();
}

//=============================================================================
// 更新
//=============================================================================
void UDPServerViewer::Update(void)
{
}

//=============================================================================
// 描画
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
// 受信スレッド(マルチスレッド用)
//=============================================================================
void UDPServerViewer::CreateRankViewer(std::vector<string> SplitedStr)
{
	// 0番 = プレイヤーの名前、1番 = AIレベル
	RankViewer* Rank = new RankViewer(SplitedStr.at(0), SplitedStr.at(1));
	Ranking.push_back(Rank);
	//ConnectedNum++;
}

#if 0
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
#endif
//=============================================================================
// ランキングの順番を決める
//=============================================================================
void UDPServerViewer::SortRanking(void)
{

}
