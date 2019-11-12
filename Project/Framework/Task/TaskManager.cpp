//=====================================
//
//�^�X�N�}�l�[�W������[TaskManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TaskManager.h"
#include "DelayedTask.h"
#include "PeriodicTask.h"
#include "Task.h"
#include "../Tool/DebugWindow.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�x���^�X�N�쐬����
***************************************/
TaskHandle TaskManager::CreateDelayedTask(int delay, const std::function<void(void)>& task)
{
	std::shared_ptr<DelayedTask> ptr = std::make_shared<DelayedTask>(delay, task);
	taskList.push_back(ptr);

	return TaskHandle(ptr);
}

/**************************************
����^�X�N�쐬����
***************************************/
TaskHandle TaskManager::CreatePeriodicTask(int interval, const std::function<void(void)>& task)
{
	std::shared_ptr<PeriodicTask> ptr = std::make_shared<PeriodicTask>(interval, task);
	taskList.push_back(ptr);

	return TaskHandle(ptr);
}

/**************************************
TaskManager�X�V����
***************************************/
void TaskManager::Update()
{
	//�I�������^�X�N���폜
	taskList.remove_if([](std::shared_ptr<Task> task)
	{
		return task->IsFinished();
	});

	//�^�X�N���s
	for (auto&& task : taskList)
	{
		task->Run();
	}
}

/**************************************
TaskHandle�R���X�g���N�^
***************************************/
TaskHandle::TaskHandle()
{

}

/**************************************
TaskHandle�R���X�g���N�^
***************************************/
TaskHandle::TaskHandle(std::shared_ptr<Task> task) :
	task(task)
{
}

/**************************************
TaskHandle�f�X�g���N�^
***************************************/
TaskHandle::~TaskHandle()
{

}

/**************************************
TaskHandle������Z�q
***************************************/
TaskHandle & TaskHandle::operator=(const TaskHandle & src)
{
	task.reset();
	task = src.task;

	return *this;
}

/**************************************
TaskHandle��~����
***************************************/
void TaskHandle::Stop()
{
	std::shared_ptr<Task> ptr = task.lock();
	if (ptr)
	{
		ptr->Stop();
	}
}

/**************************************
TaskHandle�ĊJ����
***************************************/
void TaskHandle::Resume()
{
	std::shared_ptr<Task> ptr = task.lock();
	if (ptr)
	{
		ptr->Resume();
	}
}

/**************************************
TaskHandle���f����
***************************************/
void TaskHandle::Pause()
{
	std::shared_ptr<Task> ptr = task.lock();
	if (ptr)
	{
		ptr->Pause();
	}
}
