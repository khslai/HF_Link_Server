//=============================================================================
//
// レベルアップ中継クラス [LevelUpViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _LevelUpViewer_H_
#define _LevelUpViewer_H_

#include <string>
#include <vector>
#include <functional>
#include "BaseViewer.h"

class TextureDrawer;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class LevelUpViewer : public BaseViewer
{
private:
	int State;								// 状態
	int CountFrame;

	TextureDrawer* Celebration;
	std::vector<TextureDrawer*> Text;

public:
	std::function<void(void)> Recovery;

	LevelUpViewer(std::function<void(void)> recovery);
	~LevelUpViewer();
	void Update(void) override;
	void Draw(void) override;
	void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) override;
};

#endif
