//=====================================
//
//�x�[�X�G�~�b�^�w�b�_[BaseEmitter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEEMITTER_H_
#define _BASEEMITTER_H_

#include "../../main.h"
#include "BaseParticle.h"

#include <vector>
#include <functional>

/**************************************
BaseEmitter�N���X
***************************************/
class BaseParticle;

class BaseEmitter : public GameObject
{
public:
	BaseEmitter();
	BaseEmitter(int emitNum);
	BaseEmitter(int emitNum, int duration);
	BaseEmitter(int emitNum, int durationMin, int durationMax);
	BaseEmitter(int emitNumMin, int emitNumMax, int durationMin, int durationMax);

	virtual ~BaseEmitter();

	virtual void Init(std::function<void(void)>& callback);
	virtual void Update();
	virtual bool Emit(std::vector<BaseParticle*>& container);

	virtual bool IsActive() const override;

protected:
	int cntFrame;
	int duration;
	int emitNum;

	std::function<void(void)> callback;
};

#endif