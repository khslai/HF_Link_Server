//=====================================
//
//�^�X�N�w�b�_[Task.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TASK_H_
#define _TASK_H_

#include <functional>

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
Task�N���X
***************************************/
class Task
{
public:
	Task(const std::function<void(void)>&);
	~Task();

	virtual void Run() = 0;		//���s����
	virtual void Stop();		//��~����
	virtual void Resume();		//�ĊJ�����i��x��~�����^�X�N�͍ĊJ�ł��Ȃ��j
	virtual void Pause();		//���f����
	virtual bool IsFinished();	//�I������

	//��Ԓ�`
	enum State
	{
		Idle,		//���s��
		Paused,		//�ꎞ��~��
		Finished	//�I����
	};

protected:
	std::function<void(void)> func;	//��������^�X�N
	State state;					//���݂̏��
};

#endif