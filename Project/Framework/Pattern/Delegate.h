//=====================================
//
// Delegate.h
// �@�\:
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <memory>

/**************************************
Delegater���N���X�錾
***************************************/
template<class TFunc>
class Delegate;

/**************************************
Delegater���N���X��`
***************************************/
template<class TResult, class ...TArgs>
class Delegate<TResult(TArgs...)>
{
public:
	Delegate() {}
	virtual ~Delegate() {}

	virtual TResult operator()(TArgs... args) = 0;
};

/**************************************
Delegater�N���X
***************************************/
template<class TObject, class TFunc>
class DelegateObject;

template <class TObject, class TResult, class ...TArgs>
class DelegateObject<TObject, TResult(TArgs...)> : public Delegate<TResult(TArgs...)>
{
	typedef TResult(TObject::*EventFunc)(TArgs...);
public:
	DelegateObject() :
		object(NULL), func(NULL) {}

	virtual ~DelegateObject() {}

	//�֐����s�̃I�y���[�^
	virtual TResult operator()(TArgs... args)
	{
		return (object->*func)(args...);
	}

	//�I�u�W�F�N�g�Ɗ֐��̓o�^����
	void Set(TObject* object, EventFunc func)
	{
		this->object = object;
		this->func = func;
	}

	//�f���Q�[�^�쐬����
	static Delegate<TResult(TArgs...)>* Create(TObject* object, TResult(TObject::*func)(TArgs...))
	{
		DelegateObject<TObject, TResult(TArgs...)>* delegate = new DelegateObject<TObject, TResult(TArgs...)>;
		delegate->Set(object, func);
		return  delegate;
	}

protected:
	TObject *object;			//�I�u�W�F�N�g
	EventFunc func;			//�֐��|�C���^
};

#endif
