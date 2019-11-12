//=====================================
//
//FIeldCamera.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "FieldCamera.h"
#include "State/FieldCameraFront.h"
#include "../../Framework/Input/input.h"

/**************************************
コンストラクタ
***************************************/
FieldCamera::FieldCamera() :
	//targetObject(NULL),
	startPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	goalPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), 
	cntFrame(0),
	currentMode(Mode::FrontSide)
{
	////パラメータ設定
	//const float CameraAngleXZ = D3DXToRadian(45.0f);
	//const float CameraAngleY = D3DXToRadian(60.0f);
	//const float CameraLength = 50.0f;

	//const D3DXVECTOR3 InitPos = D3DXVECTOR3(
	//	cosf(CameraAngleY) * cosf(CameraAngleXZ),
	//	sinf(CameraAngleY),
	//	cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	//ステートマシン作成
	fsm.resize(Mode::Max);
	fsm[Mode::FrontSide] = new FieldCameraFront();
}

/**************************************
デストラクタ
***************************************/
FieldCamera::~FieldCamera()
{
	Utility::DeleteContainer(fsm);
}

/**************************************
更新処理
***************************************/
void FieldCamera::Update()
{
	//ステートの更新
	fsm[currentMode]->OnUpdate(*this);

	Camera::Update();
}

/**************************************
モード切替処理
***************************************/
void FieldCamera::ChangeMode(Mode next)
{
	currentMode = next;

	fsm[currentMode]->OnStart(*this);
}

///**************************************
//追従目標設定処理
//***************************************/
//void FieldCamera::SetFollowTarget(GameObject * object)
//{
//	targetObject = object;
//}

/**************************************
追従目標座標設定処理
***************************************/
void FieldCamera::SetTargetPos(D3DXVECTOR3 TargetPos)
{
	this->TargetPos = TargetPos;
}