//=====================================
//
//�x���^�X�N����[DelayedTask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "DelayedTask.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
DelayedTask::DelayedTask(int delay, const std::function<void(void)>& task) :
	cntFrame(0),
	Delay(delay),
	Task(task)
{

}

/**************************************
���s����
***************************************/
void DelayedTask::Run()
{
	if (state != State::Idle)
		return;

	cntFrame++;

	if (cntFrame == Delay)
	{
		func();
		state = State::Finished;
	}
}
