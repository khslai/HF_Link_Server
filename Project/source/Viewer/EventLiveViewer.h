//=============================================================================
//
// �C�x���g���p�N���X [EventLiveViewer.h]
// Author : HAL���� GP12B332 41 ���M��
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
// �N���X��`
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
