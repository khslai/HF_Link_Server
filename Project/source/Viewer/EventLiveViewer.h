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
#include "BaseViewer.h"

using namespace std;

class TextureDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EventLiveViewer : public BaseViewer
{
private:
	int CountFrame;
	bool InActive;
	TextureDrawer *Background;
	TextureDrawer *EventMessage;

public:
	EventLiveViewer();
	~EventLiveViewer();
	void Update(void) override;
	void Draw(void) override;
	void ReceivePacket(int PacketType, const std::vector<string>& SpliteStr);
};

#endif
