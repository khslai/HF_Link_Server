//=====================================
//
//�w�L�T�g�����W�V�����w�b�_[HexaRotTransitionMask.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _HEXAROTTRANSITIONMASK_H_
#define _HEXAROTTRANSITIONMASK_H_

#include "../../main.h"
#include "BaseTransitionMask.h"
#include "../Math/Easing.h"
#include "../Renderer2D/Polygon2D.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class RotationHexa;
class HexaRotTransitionMask : public BaseTransitionMask
{
public:
	HexaRotTransitionMask();
	~HexaRotTransitionMask();

	MaskResult Update();
	void Draw();
	void Set(bool isTransitionOut);

private:
	int cntFrame;
	RotationHexa *hex;
};

/**************************************
��]�Z�p�`�N���X
***************************************/
class RotationHexa : public Polygon2D
{
	using Polygon2D::Polygon2D;
public:
	void Init(bool isTransitionOut);
	void Update();
};

#endif