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

class SplitTextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventLiveViewer : public BaseViewer
{
private:
	int State;								// ���
	int CountFrame;
	bool InActive;
	int TelopBGIndex;
	int MessageIndex;
	SplitTextureDrawer *TelopBG;
	SplitTextureDrawer *EventMessage;

public:
	EventLiveViewer();
	~EventLiveViewer();
	void Start(void) override;
	bool Update(void) override;
	void Draw(void) override;
	void Exit(void) override;
	void ReceivePacket(int PacketType, const std::vector<string>& SpliteStr);
};

#endif
