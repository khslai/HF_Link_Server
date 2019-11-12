//=============================================================================
//
// UDPサーバー描画クラス [UDPServerViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _UDPServerViewer_H_
#define _UDPServerViewer_H_

#include <string>
#include <vector>

using namespace std;

class TextViewer;

typedef struct DrawViewer
{
	TextViewer* Text;
	sockaddr_in Address;
}DrawViewer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class UDPServerViewer
{
private:
	int ConnectedNum;
	TextViewer *TitleText;
	std::vector<DrawViewer> DrawList;

public:
	UDPServerViewer();
	~UDPServerViewer();
	void Update(void);
	void Draw(void);
	void PushbackViewer(sockaddr_in Address);
	void SetMessage(const char * Message, sockaddr_in Address);
	void SetMessage(std::vector<string> SplitedStr, sockaddr_in Address);
};

#endif
