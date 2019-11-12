//=====================================
//
//�g�����W�V�����R���g���[���w�b�_[TransitionController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TRANSITIONCONTROLLER_H_
#define _TRANSITIONCONTROLLER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"

#include <vector>
#include <functional>

/**************************************
�O���錾
***************************************/
class Polygon2D;
class BaseTransitionMask;

/**************************************
�}�N����`
***************************************/
enum TransitionType
{
	HexaRotation,
	HexaPop,
	Mist,
	TransitionMax
};

/**************************************
�N���X��`
***************************************/
class TransitionController : public BaseSingleton<TransitionController>
{
	friend class BaseSingleton<TransitionController>;

public:
	virtual void Update();
	virtual void DrawMask();
	virtual void DrawTransition();

	virtual bool SetTransition(bool isOut, TransitionType type, std::function<void(void)> callback = NULL);

protected:
	TransitionController();
	~TransitionController();

	std::vector<BaseTransitionMask*> maskContainer;
	Polygon2D* transitionBG;

	std::function<void(void)> callback;
	
	TransitionType usingMask;

	bool isRunning;
	bool isDrawBG;

	
};

#endif