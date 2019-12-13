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
		InsertRank,		// �����L���O�ǉ�
		EventLive,		// �C�x���g���p
		LevelUp,		// ���x���A�b�v
		GetLastScore,	// �ŉ��ʂ̃X�R�A���擾
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

// �p�P�b�g�̐擪������
const string PacketHeader = "�����Link��p�̒ʐM�p�P�b�g�ł�";	

#endif