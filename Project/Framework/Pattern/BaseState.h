//=============================================================================
//
// �X�e�[�g�C���^�[�t�F�[�X�w�b�_ [BaseState.h]
// Author : ���ԗY��
//
//=============================================================================
#ifndef _BASESTATE_H_
#define _BASESTATE_H_

#define STATE_CONTINUOUS	(0)		//�X�e�[�g�𑱍s����
#define STATE_FINISHED		(1)		//�X�e�[�g�͏I������

/*****************************************************
IStateMachine�N���X
�p�����OnUpdate(), OnStart()����������
*****************************************************/
template <class T, class ENUM>
class BaseState {
public:
	virtual ENUM OnUpdate(T& entity) = 0;
	virtual void OnStart(T& entity) = 0;
};

#endif