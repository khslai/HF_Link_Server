//=============================================================================
//
// �C�x���g�R���t�B�O [EventConfig.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _EventConfig_H_
#define _EventConfig_H_

namespace EventConfig
{
	enum EventType
	{
		LinkLevelUp,		// ��̒��̃����N���x���㏸
		NewCity,			// �V�������A���A���o��
		StockRecovery,		// �h�����̃X�g�b�N���𑝂₷
		FamousPeople,		// �X�̔��W�x�v�Z�ɔ{����������
		AllLinkLevelUp,		// �����q�����Ă���X�S�̂̃����N���x���㏸
		AILevelUp,			// �X���b�g���񂵂�AI���W���x���Ƀ{�[�i�X
		TimeRecovery,		// �������Ԃ̉�
		CityDestroy,		// ������
		AILevelDecrease,	// AI���W���x������
		BanStockUse,		// ��莞�ԓ���`�b�v�g�p�s��
		LinkLevelDecrease,	// ���̃����N���x������
		NoEvent = -1,		// �C�x���g�Ȃ�
	};
}

#endif