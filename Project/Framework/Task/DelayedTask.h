//=====================================
//
//�x���^�X�N�w�b�_[DelayedTask.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DELAYEDTASK_H_
#define _DELAYEDTASK_H_

#include "Task.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
DelayedTask�N���X
***************************************/
class DelayedTask : public Task
{
public:
	DelayedTask(int delay, const std::function<void(void)>& task);	//�R���X�g���N�^

private:
	void Run();			//���s����
	
	int cntFrame;		//�t���[���J�E���g
	const int Delay;	//�x���t���[��
};

#endif