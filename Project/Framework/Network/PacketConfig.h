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
	enum 
	{
		InsertRank,
		EventLive,
		LevelUp,
		GetLastScore,
	};

	enum 
	{
		Header = 0,
		Type = 1,
		// �����L���O�ǉ��p
		PlayerName = 2,
		AILevel = 3,
		// �C�x���g�����p
		EventNo = 2,
		FieldLevel = 3,
		Max,
	};
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