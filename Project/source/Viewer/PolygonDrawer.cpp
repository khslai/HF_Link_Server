//=====================================
//
// 板ポリゴン描画クラス[PolygonDrawer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=====================================
#include "../../main.h"
#include "PolygonDrawer.h"

#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Math/Easing.h"


/**************************************
マクロ定義
***************************************/
const float FadeInZ = 100.0f;
const float FadeOutZ = 30.0f;
const float VisibleFromZ = 120.0f;
const float VisibleToZ = 10.0f;


/**************************************
コンストラクタ
***************************************/
PolygonDrawer::PolygonDrawer(const char* Tag, D3DXVECTOR3 Pos) :
	BoardPolygon(),
	Pos(Pos),
	Rot(Vector3::Zero),
	Scale(Vector3::One),
	Movable(false)
{
	ResourceManager::Instance()->GetPolygon(Tag, this);
}

/**************************************
コンストラクタ
***************************************/
PolygonDrawer::PolygonDrawer(const char* Tag, D3DXVECTOR3 StartPos, D3DXVECTOR3 DestPos) :
	BoardPolygon(),
	Pos(StartPos),
	Rot(Vector3::Zero),
	Scale(Vector3::One),
	StartPos(StartPos),
	DestPos(DestPos),
	Movable(true)
{
	ResourceManager::Instance()->GetPolygon(Tag, this);
	float RotRadianY = 0.0f;
	if (DestPos.x > StartPos.x)
	{
		RotRadianY = atanf(fabsf(DestPos.z - StartPos.z) / fabsf(DestPos.x - StartPos.x));
	}
	else if (DestPos.x < StartPos.x)
	{
		RotRadianY = -atanf(fabsf(DestPos.z - StartPos.z) / fabsf(DestPos.x - StartPos.x));
	}
	float test = D3DXToRadian(88.0f);
	Rot = D3DXVECTOR3(0.0f, RotRadianY, 0.0f);
}

/**************************************
デストラクタ
***************************************/
PolygonDrawer::~PolygonDrawer()
{
}

/**************************************
更新処理
***************************************/
void PolygonDrawer::Update(void)
{
	if (Movable)
	{
		CountFrame++;
		float Time = CountFrame / 300;
		Pos = Easing::EaseValue(Time, StartPos, DestPos, EaseType::Linear);

		if (Pos == DestPos)
		{
			Pos = StartPos;
			CountFrame = 0;
		}
	}
}

/**************************************
描画処理
***************************************/
void PolygonDrawer::Draw()
{
	Transform transform = Transform(Pos, Rot, Scale);
	D3DXMATRIX WorldMatrix = transform.GetMatrix();

	if (Movable)
	{
		SetFade(WorldMatrix);
	}

	BoardPolygon::Draw(WorldMatrix);
}

/**************************************
UVインデックス設定処理
***************************************/
void PolygonDrawer::SetTextureIndex(int index)
{
	BoardPolygon::SetTextureIndex(index);
}

/**************************************
座標設定処理
***************************************/
void PolygonDrawer::SetPosition(const D3DXVECTOR3& Pos)
{
	this->Pos = Pos;
}

/**************************************
回転設定処理
***************************************/
void PolygonDrawer::SetRotation(const D3DXVECTOR3 & Rot_Degree)
{
	this->Rot = D3DXVECTOR3(
		D3DXToRadian(Rot_Degree.x),
		D3DXToRadian(Rot_Degree.y),
		D3DXToRadian(Rot_Degree.z));
}


/**************************************
フェイド処理
***************************************/
void PolygonDrawer::SetFade(D3DXMATRIX& WorldMatrix)
{
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		D3DXCOLOR Color = pVtx[i].diffuse;
		D3DXVECTOR3 VtxPos = Vector3::Zero;
		float Alpha = 0.0f;

		D3DXVec3TransformCoord(&VtxPos, &pVtx[i].vtx, &WorldMatrix);

		//位置が描画する範囲より遠かったら透過0
		if (VtxPos.z > VisibleFromZ)
		{
			Alpha = 0.0f;
		}
		//(近づいている場合)フェードインする位置だったら
		else if (VtxPos.z < VisibleFromZ && VtxPos.z >= FadeInZ)
		{
			Alpha = 1.0f * (VisibleFromZ - VtxPos.z) / (VisibleFromZ - FadeInZ);
		}
		//通常描画する位置なら
		else if (VtxPos.z <= FadeInZ && VtxPos.z >= FadeOutZ)
		{
			Alpha = 1.0f;
		}
		//(近づいてる場合)フェードアウトする位置だったら
		else if (VtxPos.z <= FadeOutZ && VtxPos.z > VisibleToZ)
		{
			Alpha = 1.0f - (1.0f * (FadeOutZ - VtxPos.z) / (FadeOutZ - VisibleToZ));
		}
		//描画する範囲より近かったら透過
		else if (VtxPos.z < VisibleToZ)
		{
			Alpha = 0.0f;
		}

		Color.a = Alpha;
		pVtx[i].diffuse = Color;
	}

	vtxBuff->Unlock();
}

