//=============================================================================
//
// ���M�p�P�b�g�p�����[�^�N���X [PacketConfig.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _PacketConfig_H_
#define _PacketConfig_H_

#include <string>

using namespace std;

namespace Packet
{
	enum Viewer
	{
		NoEvent,
		ShowRanking,
		ShowEvent,
		ShowLevelUp,
	};

	namespace Rank
	{
		enum
		{
			Header,
			Type,
			PlayerName,
			AILevel,
		};
	}

	namespace Event
	{
		enum
		{
			Header,
			Type,
			EventNo,
		};
	}

	namespace LevelUp
	{
		enum
		{
			Header,
			Type,
			FieldLevel,
		};
	}
}

// �g�p����|�[�g�ԍ�
const int ServerPort = 8080;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class PacketConfig
{
public:
	string Header = "�����Link��p�̒ʐM�p�P�b�g�ł�";	// �p�P�b�g�̐擪������
	int PacketType = 0;									// �N���鎖�������
	string PlayerName = "Potato";						// �v���C���[�̖��O
	int AILevel = 0;									// AI���x��
};

#endif