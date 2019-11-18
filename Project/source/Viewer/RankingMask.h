//=============================================================================
//
// �����L���O�}�X�N�N���X [RankingMask.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _RankingMask_H_
#define _RankingMask_H_

#include "../../Framework/Renderer2D/Polygon2D.h"
#include "../../Framework/Transition/BaseTransitionMask.h"

/**************************************
�N���X��`
***************************************/
class RectangleMask;
class RankingMask : public BaseTransitionMask
{
public:
	RankingMask(D3DXVECTOR3 Pos);
	~RankingMask();

	MaskResult Update();
	void Draw();
	void Set(bool isTransitionOut);
	void Set(void);

private:
	int cntFrame;
	RectangleMask *rect;
};

/**************************************
��`�N���X
***************************************/
class RectangleMask : public Polygon2D
{
public:
	void Init(void);
	void Update(void);
};

#endif