//=====================================
//
// フィールドカメラ(正面)クラス[FieldCameraFront.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "FieldCameraFront.h"
#include "../../../Framework/Math/Easing.h"
#include "../../../Framework/Tool/DebugWindow.h"

/**************************************
入場処理
***************************************/
void FieldCamera::FieldCameraFront::OnStart(FieldCamera & entity)
{
	//パラメータ初期化
	//entity.startPosition = entity.transform.GetPosition() - entity.target;
	//entity.cntFrame = 0;
	//entity.startTarget = entity.target;

	//移動先の座標を設定
	//const float CameraAngleXZ = D3DXToRadian(90.0f);
	//const float CameraAngleY = D3DXToRadian(90.0f);
	//const float CameraLength = 10.0f;

	//entity.goalPosition = D3DXVECTOR3(
	//	cosf(CameraAngleY) * cosf(CameraAngleXZ),
	//	sinf(CameraAngleY),
	//	cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	//entity.transform.SetRotation(D3DXVECTOR3(CameraAngleY, CameraAngleXZ, 0.0f));
}

/**************************************
更新処理
***************************************/
FieldCamera::Mode FieldCamera::FieldCameraFront::OnUpdate(FieldCamera & entity)
{
	//entity.cntFrame++;

	//イージングで移動
	//const float MoveDuration = 30;
	//float t = entity.cntFrame / MoveDuration;
	//D3DXVECTOR3 position = Easing::EaseValue(t, entity.startPosition, entity.goalPosition, EaseType::OutCubic);

	//追従目標の座標を注視点に設定
	//D3DXVECTOR3 target = Easing::EaseValue(t, entity.startTarget, entity.targetObject->GetPosition(), EaseType::OutCubic);
	//D3DXVECTOR3 target = Easing::EaseValue(t, entity.startTarget, entity.TargetPos, EaseType::OutCubic);
	//entity.target = target;

	//追従目標に合わせて視点を設定
	//entity.transform.SetPosition(position + target);

	return FieldCamera::FrontSide;
}