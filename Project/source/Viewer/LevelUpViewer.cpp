//=============================================================================
//
// レベルアップ中継クラス [LevelUpViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../main.h"
#include "LevelUpViewer.h"
#include "Framework/TextureDrawer.h"
#include "../Effect/GameParticleManager.h"
#include "../Viewer/ViewerConfig.h"
#include "../Actor/RobotActor.h"
#include "../Sound/SoundConfig.h"

#include "../../Framework/Sound/SoundEffect.h"
#include "../../Framework/Network/PacketConfig.h"
#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Task/TaskManager.h"


const int CharNum = 16;
const float ScaleNum = 3;

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
LevelUpViewer::LevelUpViewer(std::function<void(void)> recovery) :
	Recovery(recovery)
{
	const D3DXVECTOR3 FirstCharPos = D3DXVECTOR3(SCREEN_CENTER_X - (CharNum / 2 - 1) * 100.0f, SCREEN_CENTER_Y, 0.0f);

	Celebration = new TextureDrawer(D3DXVECTOR2(700.0, 280.0f), false);
	Celebration->LoadTexture("data/TEXTURE/Viewer/LevelUpViewer/Celebration.png");
	Celebration->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y - 200.0f, 0.0f));

	// 文字の設定
	Text.reserve(CharNum);
	for (int i = 0; i < CharNum; i++)
	{
		Text.push_back(new TextureDrawer(D3DXVECTOR2(1600.0f, 200.0f), CharNum, 2, false));
		Text.at(i)->LoadTexture("data/TEXTURE/Viewer/LevelUpViewer/Text.png");
		Text.at(i)->SetPosition(FirstCharPos + D3DXVECTOR3(100.0f * i, 0.0f, 0.0f));
		Text.at(i)->SetIndex(i);
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
LevelUpViewer::~LevelUpViewer()
{
	SAFE_DELETE(Celebration);
	Utility::DeleteContainer(Text);
}

//=============================================================================
// 更新
//=============================================================================
void LevelUpViewer::Update(void)
{
	Celebration->Update();

	for (auto &text : Text)
	{
		text->Update();
	}
}

//=============================================================================
// 描画
//=============================================================================
void LevelUpViewer::Draw(void)
{
	Celebration->Draw();

	for (auto &text : Text)
	{
		text->Draw();
	}
}

//=============================================================================
// パケットの内容を処理
//=============================================================================
void LevelUpViewer::ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr)
{
	if (PacketType != Packet::LevelUp)
		return;

	static int Num = 0;

	// 初期化
	SE::Play(SoundConfig::Clapping);
	Celebration->SetAlpha(1.0f);
	Celebration->SetVisible(false);

	for (auto &text : Text)
	{
		// 初期化
		text->SetAlpha(1.0f);
		text->SetScale(ScaleNum);
		text->SetIndex(Num);
		text->SetVisible(false);

		// 縮小
		TaskManager::Instance()->CreateDelayedTask((10 * (Num + 1)), [&]()
		{
			text->SetScale(30.0f, 1 / ScaleNum, InQuart, [&]()
			{
				GameParticleManager::Instance()->SetColorfulDebris(text->GetPosition());
				text->SetIndex(Num);
				Num++;
			});
			text->SetVisible(true);
		});

		// フェイドアウト
		TaskManager::Instance()->CreateDelayedTask(360, [&]()
		{
			text->Fade(60.0f, 0.0f);
		});
		Num++;
	}

	// 展開
	TaskManager::Instance()->CreateDelayedTask(200, [&]()
	{
		Celebration->Expand(60.0f, ExpandType::LeftToRight, EaseType::InQuart);
		RobotActor::ChangeAnim(RobotActor::Cheering);

		SE::Play(SoundConfig::FieldLevelUp);
	});
	// フェイドアウト
	TaskManager::Instance()->CreateDelayedTask(360, [&]()
	{
		Celebration->Fade(60.0f, 0.0f);
	});

	// ランキング復帰
	TaskManager::Instance()->CreateDelayedTask(480, [&]()
	{
		Num = 0;
		SE::Stop(SoundConfig::FieldLevelUp);
		SE::Stop(SoundConfig::Clapping);
		Recovery();
	});
}
