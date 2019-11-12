//=====================================
//
// シティアクター[CityActor.cpp]
// 機能：都市（国、星）用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "CityActor.h"
#include "../../Framework/Resource/ResourceManager.h"

//=====================================
// コンストラクタ
//=====================================
CityActor::CityActor(const D3DXVECTOR3& Pos) :
	PlaceActor(Pos)
{
	// モデルデータ参照
	ResourceManager::Instance()->GetMesh("Town-City", mesh);
	mesh->SetWireframePara();
	//ResourceManager::Instance()->GetMesh("Town-Space", mesh);

	type = Field::Model::Town;
}

//=====================================
// デストラクタ
//=====================================
CityActor::~CityActor()
{
}
