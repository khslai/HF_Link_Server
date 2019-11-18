//=============================================================================
//
// ランキングマスククラス [RankingMask.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _RankingMask_H_
#define _RankingMask_H_

#include "../../Framework/Renderer2D/Polygon2D.h"
#include "../../Framework/Transition/BaseTransitionMask.h"

/**************************************
クラス定義
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
矩形クラス
***************************************/
class RectangleMask : public Polygon2D
{
public:
	void Init(void);
	void Update(void);
};

#endif