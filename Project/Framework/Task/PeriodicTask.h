//=====================================
//
//����^�X�N�w�b�_[PeriodicTask.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PERIODICTASK_H_
#define _PERIODICTASK_H_

#include "Task.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
PeriodicTask�N���X
***************************************/
class PeriodicTask : public Task
{
public:
	PeriodicTask(int interval, const std::function<void(void)>& task);	//�R���X�g���N�^

private:	
	void Run();			//���s����

	int cntFrame;		//�t���[���J�E���g
	const int Interval;	//�C���^�[�o��
};

#endif