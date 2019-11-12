//=====================================
//
//FieldCamera.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDCAMERA_H_
#define _FIELDCAMERA_H_

#include "../../Framework/Camera/Camera.h"
#include "../../Framework/Pattern/BaseState.h"
#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class FieldCamera : public Camera
{
public:
	//カメラモードを表す列挙子
	enum Mode
	{
		FrontSide,				//クォータービューモード
		Max
	};

	//コンストラクタ、デストラクタ
	FieldCamera();
	~FieldCamera();

	//更新処理
	void Update();

	//モード切替処理
	void ChangeMode(Mode next);

	//追従目標設定処理
	//void SetFollowTarget(GameObject* object);

	//追従目標座標設定処理
	void SetTargetPos(D3DXVECTOR3 TargetPos);

private:
	//GameObject *targetObject;						//追従目標
	D3DXVECTOR3 TargetPos;							//追従目標の座標
	D3DXVECTOR3 startPosition, goalPosition;		//イージング用座標
	D3DXVECTOR3 startTarget;						//イージング用注視点

	int cntFrame;									//フレームカウント

	Mode currentMode;								//現在のモード
	std::vector<BaseState<FieldCamera, Mode>*> fsm;	//ステートマシン
	
	//ステートクラス
	class FieldCameraFront;
};

#endif