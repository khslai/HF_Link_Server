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

using namespace std;

class TextureDrawer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventLiveViewer
{
private:

public:
	EventLiveViewer();
	~EventLiveViewer();
	void Update(void);
	void Draw(void);
};

#endif
