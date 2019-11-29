//=============================================================================
//
// イベント中継クラス [EventLiveViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _EventLiveViewer_H_
#define _EventLiveViewer_H_

#include <string>
#include <vector>
#include <functional>
#include "BaseViewer.h"

using namespace std;

class TextureDrawer;

enum FieldLevel
{
	City,
	World,
	Space,
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventLiveViewer : public BaseViewer
{
private:
	int State;								// 状態
	int CountFrame;
	bool ActionFlag;
	int TelopBGIndex;
	int MessageIndex;
	TextureDrawer *TelopBG;
	TextureDrawer *EventMessage;

public:
	std::function<void(void)> Recovery;

	EventLiveViewer(std::function<void(void)> recovery);
	~EventLiveViewer();
	bool Update(void) override;
	void Draw(void) override;
	void SetState(int State) { this->State = State; };
	void SetActionFlag(bool Flag) { this->ActionFlag = Flag; };
	void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) override;
};

#endif
