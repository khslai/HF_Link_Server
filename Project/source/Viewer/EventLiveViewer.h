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

using namespace std;

class TextureDrawer;

//*****************************************************************************
// クラス定義
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
