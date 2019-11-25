//=============================================================================
//
// ロボットクラス [RobotActor.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _RobotActor_H_
#define _RobotActor_H_

#include "PlaceActor.h"

//**************************************
// クラス定義
//**************************************
class RobotActor : public PlaceActor
{
public:
	RobotActor(const D3DXVECTOR3& pos);
	~RobotActor();
};

#endif
