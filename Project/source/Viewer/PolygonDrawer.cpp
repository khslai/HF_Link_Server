//=====================================
//
// �|���S���`��N���X[PolygonDrawer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "../../main.h"
#include "PolygonDrawer.h"

#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Math/Easing.h"

typedef struct DataStruct
{
	float IntervalZ;
	float MoveSpeed;
}DataStruct;


/**************************************
�}�N����`
***************************************/
const DataStruct PolygonData[Max] =
{
	{75.0f, 0.5f},
	{20.0f, 0.2f},
};



/**************************************
�R���X�g���N�^
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
�R���X�g���N�^
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
}

/**************************************
�R���X�g���N�^
***************************************/
PolygonDrawer::PolygonDrawer(const char* Tag, D3DXVECTOR3 StartPos, D3DXVECTOR3 DestPos, int Num) :
	BoardPolygon(),
	Pos(StartPos),
	Rot(Vector3::Zero),
	Scale(Vector3::One),
	StartPos(StartPos),
	DestPos(DestPos),
	Movable(true)
{
	ResourceManager::Instance()->GetPolygon(Tag, this);
	SetPolygonPara(Tag, Num);
}

/**************************************
�f�X�g���N�^
***************************************/
PolygonDrawer::~PolygonDrawer()
{
}

/**************************************
�X�V����
***************************************/
void PolygonDrawer::Update(void)
{
	if (Movable)
	{
		D3DXVECTOR3 MoveDir = DestPos - StartPos;
		D3DXVec3Normalize(&MoveDir, &MoveDir);

		Pos += MoveDir * MoveSpeed;

		if (Pos.z <= DestPos.z)
		{
			Pos = StartPos;
		}
	}
}

/**************************************
�`�揈��
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

void PolygonDrawer::SetPolygonPara(const char* Tag, int Num)
{
	float Interval = 0.0f;

	if (strcmp(Tag, "Wall") == 0)
	{
		MoveSpeed = PolygonData[MovePolygonType::Wall].MoveSpeed;
		Interval = PolygonData[MovePolygonType::Wall].IntervalZ;

		float RotRadianY = 0.0f;
		if (DestPos.x > StartPos.x)
		{
			RotRadianY = atanf(fabsf(DestPos.z - StartPos.z) / fabsf(DestPos.x - StartPos.x));
		}
		else if (DestPos.x < StartPos.x)
		{
			RotRadianY = -atanf(fabsf(DestPos.z - StartPos.z) / fabsf(DestPos.x - StartPos.x));
		}
		Rot = D3DXVECTOR3(0.0f, RotRadianY, 0.0f);
	}
	else if (strcmp(Tag, "Ground") == 0)
	{
		MoveSpeed = PolygonData[MovePolygonType::Ground].MoveSpeed;
		Interval = PolygonData[MovePolygonType::Ground].IntervalZ;

		Rot = D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f);
	}

	Pos = StartPos + D3DXVECTOR3(0.0f, 0.0f, Interval * Num);
}

/**************************************
UV�C���f�b�N�X�ݒ菈��
***************************************/
void PolygonDrawer::SetTextureIndex(int index)
{
	BoardPolygon::SetTextureIndex(index);
}

/**************************************
���W�ݒ菈��
***************************************/
void PolygonDrawer::SetPosition(const D3DXVECTOR3& Pos)
{
	this->Pos = Pos;
}

/**************************************
��]�ݒ菈��
***************************************/
void PolygonDrawer::SetRotation(const D3DXVECTOR3 & Rot_Degree)
{
	this->Rot = D3DXVECTOR3(
		D3DXToRadian(Rot_Degree.x),
		D3DXToRadian(Rot_Degree.y),
		D3DXToRadian(Rot_Degree.z));
}


/**************************************
�t�F�C�h����
***************************************/
void PolygonDrawer::SetFade(D3DXMATRIX& WorldMatrix)
{
	const float FadeInZ = 120.0f;
	const float FadeOutZ = 30.0f;
	const float VisibleFromZ = 140.0f;
	const float VisibleToZ = 10.0f;

	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		D3DXCOLOR Color = pVtx[i].diffuse;
		D3DXVECTOR3 VtxPos = Vector3::Zero;
		float Alpha = 0.0f;

		D3DXVec3TransformCoord(&VtxPos, &pVtx[i].vtx, &WorldMatrix);

		//�ʒu���`�悷��͈͂�艓�������瓧��0
		if (VtxPos.z > VisibleFromZ)
		{
			Alpha = 0.0f;
		}
		//(�߂Â��Ă���ꍇ)�t�F�[�h�C������ʒu��������
		else if (VtxPos.z < VisibleFromZ && VtxPos.z >= FadeInZ)
		{
			Alpha = 1.0f * (VisibleFromZ - VtxPos.z) / (VisibleFromZ - FadeInZ);
		}
		//�ʏ�`�悷��ʒu�Ȃ�
		else if (VtxPos.z <= FadeInZ && VtxPos.z >= FadeOutZ)
		{
			Alpha = 1.0f;
		}
		//(�߂Â��Ă�ꍇ)�t�F�[�h�A�E�g����ʒu��������
		else if (VtxPos.z <= FadeOutZ && VtxPos.z > VisibleToZ)
		{
			Alpha = 1.0f - (1.0f * (FadeOutZ - VtxPos.z) / (FadeOutZ - VisibleToZ));
		}
		//�`�悷��͈͂��߂������瓧��
		else if (VtxPos.z < VisibleToZ)
		{
			Alpha = 0.0f;
		}

		Color.a = Alpha;
		pVtx[i].diffuse = Color;
	}

	vtxBuff->Unlock();
}

