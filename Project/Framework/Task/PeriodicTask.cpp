//=====================================
//
//����^�X�N����[PeriodicTask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PeriodicTask.h"
#include "../Math/TMath.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
PeriodicTask::PeriodicTask(int interval, const std::function<void(void)>& task) :
	Task(task),
	cntFrame(0),
	Interval(interval)
{

}

/**************************************
���s����
***************************************/
void PeriodicTask::Run()
{
	if (state != State::Idle)
		return;

	cntFrame = Math::WrapAround(0, Interval, cntFrame + 1);

	if (cntFrame == 0)
	{
		func();
	}
}