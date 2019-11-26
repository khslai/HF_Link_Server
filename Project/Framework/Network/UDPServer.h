//=============================================================================
//
// UDP�T�[�o�[�N���X [UDPServer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _UDPServer_H_
#define _UDPServer_H_

#include <string>
#include <vector>
#include "../../source/Viewer/BaseViewer.h"
#include "../Pattern/BaseState.h"

using namespace std;

class Background;
class UDPServerViewer;
class EventLiveViewer;
class Transition;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class UDPServer
{
public:
	UDPServer();
	~UDPServer();
	void Update(void);
	void DrawRanking(void);
	void DrawBackground(void);

	// �}���`�X���b�h�p
	static HANDLE Thread;
	static unsigned __stdcall ThreadEntryPoint(void* This);

	//�X�e�[�g��\���񋓎q
	enum State
	{
		Ranking,
		Event,
		//LevelUp,
		Max
	};

private:
	Background *background;
	Transition *transition;
	SOCKET ServerSocket;
	State Current;
	std::vector<BaseViewer*> ViewerContainer;
	std::vector<std::vector<string>> RankStack;		// �ǉ��\��̃����N
	std::vector<sockaddr_in> ConnectedList;

	void ReceivePacket(void);
	void CreateViewerTexture(void);
};

#endif
