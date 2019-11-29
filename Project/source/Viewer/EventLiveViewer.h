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
// �N���X��`
//*****************************************************************************
class EventLiveViewer : public BaseViewer
{
private:
	int State;								// ���
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
