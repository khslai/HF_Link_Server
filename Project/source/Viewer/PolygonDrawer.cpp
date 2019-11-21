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


/**************************************
�}�N����`
***************************************/
const float FadeInZ = 100.0f;
const float FadeOutZ = 30.0f;
const float VisibleFromZ = 120.0f;
const float VisibleToZ = 10.0f;


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

