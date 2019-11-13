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

class RankViewer;
class TextureDrawer;
class TextViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServerViewer
{
private:
	//int ConnectedNum;
	TextViewer *TitleText;
	std::vector<RankViewer*> Ranking;
	//std::vector<sockaddr_in> ConnectedList;

	void SortRanking(void);

public:
	UDPServerViewer();
	~UDPServerViewer();
	void Update(void);
	void Draw(void);
	void CreateRankViewer(std::vector<string> SplitedStr);
	//void SetMessage(const char * Message, sockaddr_in Address);
	//void SetMessage(std::vector<string> SplitedStr, sockaddr_in Address);
};

#endif
