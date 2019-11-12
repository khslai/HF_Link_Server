//=====================================
//
//�~�X�g�g�����W�V�����}�X�N�w�b�_[MistTransitionMask.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MISTTRANSITIONMASK_H_
#define _MISTTRANSITIONMASK_H_

#include "../../main.h"
#include "BaseTransitionMask.h"
#include "../Math/Easing.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class MistTransitionMask : public BaseTransitionMask
{
public:
	MistTransitionMask();
	~MistTransitionMask();

	MaskResult Update() override;
	void Draw() override;
	void Set(bool isOut) override;

private:
	DWORD alphaRef;
	int cntFrame;

	float startRef, endRef;
	EaseType type;

	Polygon2D *polygon;
};

#endif