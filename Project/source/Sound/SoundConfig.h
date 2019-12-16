//=============================================================================
//
// �T�E���h�R���t�B�O�N���X [SoundConfig.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _SOUNDCONFIG_H_
#define _SOUNDCONFIG_H_

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class SoundConfig
{
public:
	// SE�̒ʂ��ԍ�
	enum SEID
	{
		// *** SE ***
		RankingInsert,		// �����L���O�ǉ�
		PlusEvent,			// �v���X�C�x���g
		MinusEvent,			// �}�C�i�X�C�x���g
		Clapping,			// ����
		FieldLevelUp,		// �t�B�[���h���x���A�b�v
		Transition,			// �V�[���J��
		SEMax
	};

	//�����t�@�C���̃p�X
	const static char* SEPath[SEID::SEMax];
};

#endif