//=============================================================================
//
// UDP�T�[�o�[�`��N���X [UDPServerViewer.h]
// Author : HAL���� GP12B332 41 ���M��
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
// �N���X��`
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
