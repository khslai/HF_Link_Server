//=============================================================================
//
// イベント中継クラス [EventLiveViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "EventLiveViewer.h"
#include "TextureDrawer.h"
#include "../Effect/GameParticleManager.h"

#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
EventLiveViewer::EventLiveViewer()
{
	Background = new TextureDrawer(1, 2, D3DXVECTOR2(SCREEN_WIDTH, 512.0f));
	Background->LoadTexture("data/TEXTURE/Viewer/EventLiveViewer/BG.png");
	Background->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));
	Background->TexExpand_ToUpDown(0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
EventLiveViewer::~EventLiveViewer()
{
	SAFE_DELETE(Background);
	SAFE_DELETE(EventMessage);
}

//=============================================================================
// 更新
//=============================================================================
void EventLiveViewer::Update(void)
{
	//if (!InActive)
	//	return;
	static bool Test = false;

	if (Debug::Button("TextureExpand"))
	{
		Test = true;
		CountFrame = 0;
	}

	if (Test)
	{
		CountFrame++;
		float Time = (float)CountFrame / 60;

		Background->TexExpand_ToUpDown(Time, 0);
	}
}

//=============================================================================
// 描画
//=============================================================================
void EventLiveViewer::Draw(void)
{
	Background->Draw();
	//EventMessage->Draw();
}

//=============================================================================
// パケットの内容を処理
//=============================================================================
void EventLiveViewer::ReceivePacket(int PacketType, const std::vector<string>& SpliteStr)
{

}
