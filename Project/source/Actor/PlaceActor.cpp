//=====================================
//
// プレイスアクター[PlaceActor.cpp]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PlaceActor.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Camera/ViewFrustum.h"
#include "../../Framework/Camera/Camera.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const D3DXVECTOR3 PlaceActor::Scale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// コンストラクタ
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& Pos)
{
	// メッシュコンテナの作成
	mesh = new MeshContainer();

	// ステータスセット
	transform->SetPosition(Pos);
	transform->SetScale(Scale);
	this->SetActive(true);
}

//=====================================
// デストラクタ
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_DELETE(mesh);
}

//=====================================
// 更新
//=====================================
void PlaceActor::Update()
{
	Rotate(1.0f);

#if _DEBUG
	Debug();
#endif
}

//=====================================
// 描画
//=====================================
void PlaceActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
	//mesh->DrawWireframe(false);
}

//=====================================
// Y軸回転
//=====================================
void PlaceActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// 座標のセット
//=====================================
void PlaceActor::SetPosition(const D3DXVECTOR3& Pos)
{
	transform->SetPosition(Pos);
}

//=====================================
// メッシュデータのカラー変更
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color)
{
	unsigned numMaterial = mesh->GetMaterialNum();

	for (unsigned i = 0; i < numMaterial; i++)
	{
		mesh->SetMaterialColor(color, i);
	}
}

//=====================================
// 座標、回転、大きさをリセット
//=====================================
void PlaceActor::ResetTransform()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	transform->SetScale(Scale);
	transform->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=====================================
// デバッグ
//=====================================
#if _DEBUG
void PlaceActor::Debug()
{

}
#endif
