//=====================================
//
//�x�[�X�g�����W�V�����w�b�_[BaseTransitionMask.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASETRANSITIONMASK_H_
#define _BASETRANSITIONMASK_H_

#include "../../main.h"

/**************************************
�}�N����`
***************************************/
enum MaskResult
{
	Continuous,
	FinishTransitionIn,
	FinishTransitionOut
};

class Polygon2D;

/**************************************
BaseTransitionMask�N���X
���p�����MaskResult Update()�ASet(bool isTransitionOut)����������
***************************************/
class BaseTransitionMask
{
public:
	BaseTransitionMask();
	virtual ~BaseTransitionMask();

	virtual MaskResult Update() = 0;

	virtual void Draw() = 0;

	virtual void Set(bool isTransitionOut) = 0;

protected:
	static const int FramePerSecond;

	bool active;
	bool isTransitionOut;

	virtual void BeginMask();
	virtual void EndMask();
};

#endif