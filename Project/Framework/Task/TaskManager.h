//=====================================
//
//�^�X�N�}�l�[�W���w�b�_[TaskManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#include "../Pattern/BaseSingleton.h"

#include <functional>
#include <memory>
#include <list>

/**************************************
�O���錾
***************************************/
class Task;
class DelayedTask;
class PeriodicTask;
class TaskHandle;

/**************************************
TaskManager�N���X
***************************************/
class TaskManager : public BaseSingleton<TaskManager>
{
	friend class BaseGame;		//Update()�̌Ăяo����BaseGame�݂̂ɋ�����������
public:
	//�x���^�X�N�쐬����
	TaskHandle CreateDelayedTask(int delay, const std::function<void(void)>& task);

	//����^�X�N�쐬����
	TaskHandle CreatePeriodicTask(int interval, const std::function<void(void)>& task);

private:
	//�X�V����
	void Update();

	//�^�X�N���X�g
	std::list<std::shared_ptr<Task>> taskList;
};

/**************************************
TaskInterface�N���X
�����������͂��̃N���X��ʂ��ă^�X�N�𑀍삷��
***************************************/
class TaskHandle
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	TaskHandle();
	TaskHandle(std::shared_ptr<Task>);
	~TaskHandle();

	//������Z�q
	TaskHandle& operator =(const TaskHandle&);

	void Stop();		//��~����
	void Resume();		//�ĊJ�����i��x��~�����^�X�N�͍ĊJ�ł��Ȃ��j
	void Pause();		//���f����

private:
	std::weak_ptr<Task> task;
};
#endif