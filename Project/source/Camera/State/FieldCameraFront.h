//=====================================
//
// フィールドカメラ(正面)クラス[FieldCameraFront.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#ifndef _FieldCameraFront_H_
#define _FieldCameraFront_H_

#include "../../../main.h"
#include "../FieldCamera.h"
#include "../../../Framework/Pattern/BaseState.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera::FieldCameraFront : public BaseState<FieldCamera, FieldCamera::Mode>
{
public:
	void OnStart(FieldCamera& entity);
	FieldCamera::Mode OnUpdate(FieldCamera& entity);
};
#endif