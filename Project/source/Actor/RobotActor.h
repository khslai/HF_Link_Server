//=============================================================================
//
// ���{�b�g�N���X [RobotActor.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _RobotActor_H_
#define _RobotActor_H_

#include "PlaceActor.h"

//**************************************
// �N���X��`
//**************************************
class RobotActor : public PlaceActor
{
public:
	RobotActor(const D3DXVECTOR3& pos);
	~RobotActor();
};

#endif
