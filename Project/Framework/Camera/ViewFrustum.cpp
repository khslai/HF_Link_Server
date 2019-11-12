//=====================================
//
//ViewFrustum.cpp
//�@�\:�J�����̎�����
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ViewFrustum.h"
#include "Camera.h"

/**************************************
static�����o
***************************************/
const unsigned ViewFrustum::VertexMax = 8;

/**************************************
�R���X�g���N�^
***************************************/
ViewFrustum::ViewFrustum()
{
	vertexPos.resize(VertexMax, Vector3::Zero);
}

/**************************************
�f�X�g���N�^
***************************************/
ViewFrustum::~ViewFrustum()
{
	vertexPos.clear();
}

/**************************************
������̖ʂ̖@���擾����
***************************************/
D3DXVECTOR3 ViewFrustum::GetNormal(Surface surfaceID)
{
	D3DXVECTOR3 normal = Vector3::Up;
	switch (surfaceID)
	{
	case ViewFrustum::Left:
		normal = _GetNormal(NearLeftTop, FarLeftTop, NearLeftBottom);
		break;

	case ViewFrustum::Right:
		normal = _GetNormal(NearRightBottom, FarRightBottom, NearRightTop);
		break;

	case ViewFrustum::Top:
		normal = _GetNormal(NearLeftTop, NearRightTop, FarLeftTop);
		break;

	case ViewFrustum::Bottom:
		normal = _GetNormal(NearLeftBottom, FarLeftBottom, NearRightBottom);
		break;
	}

	return normal;
}

/**************************************
���_�ݒ菈��
***************************************/
void ViewFrustum::SetVertex(const D3DXVECTOR3 & NearLeftTop, const D3DXVECTOR3 & NearRightTop, const D3DXVECTOR3 & NearLeftBottom, const D3DXVECTOR3 & NearRightBottom, const D3DXVECTOR3 & FarLeftTop, const D3DXVECTOR3 & FarRightTop, const D3DXVECTOR3 & FarLeftBottom, const D3DXVECTOR3 & FarRightBottom)
{
	vertexPos[Vertex::NearLeftTop] = NearLeftTop;
	vertexPos[Vertex::NearRightTop] = NearRightTop;
	vertexPos[Vertex::NearLeftBottom] = NearLeftBottom;
	vertexPos[Vertex::NearRightBottom] = NearRightBottom;
	vertexPos[Vertex::FarLeftTop] = FarLeftTop;
	vertexPos[Vertex::FarRightTop] = FarRightTop;
	vertexPos[Vertex::FarLeftBottom] = FarLeftBottom;
	vertexPos[Vertex::FarRightBottom] = FarRightBottom;

}

/**************************************
�@���擾�����i���������j
***************************************/
D3DXVECTOR3 ViewFrustum::_GetNormal(int v1, int v2, int v3)
{
	return Vector3::Axis(vertexPos[v2] - vertexPos[v1], vertexPos[v3] - vertexPos[v1]);
}

/**************************************
�ʏ�̂����_������
***************************************/
D3DXVECTOR3 ViewFrustum::GetSurfacePoint(Surface surfaceID)
{
	D3DXVECTOR3 ret = Vector3::Zero;
	switch (surfaceID)
	{
	case Left:
		ret = vertexPos[NearLeftTop];
		break;
	case Right:
		ret = vertexPos[NearRightTop];
		break;
	case Top:
		ret = vertexPos[NearLeftTop];
		break;
	case Bottom:
		ret = vertexPos[FarLeftBottom];
		break;
	default:
		break;
	}

	return ret;
}

/**************************************
������J�����O
***************************************/
bool ViewFrustum::CheckOnCamera(const D3DXVECTOR3 target, const float size)
{
	bool ret = false;

	for (int i = 0; i < Surface::Max; i++)
	{
		D3DXVECTOR3 nor = GetNormal(Surface(i));
		D3DXVECTOR3 surfacePoint = GetSurfacePoint(Surface(i));

		D3DXVECTOR3 positiveDist = GetPositivePoint(target, size, nor) - surfacePoint;
		D3DXVECTOR3 negativeDist = GetNegativePoint(target, size, nor) - surfacePoint;

		// ��������
		float dp = D3DXVec3Dot(&positiveDist, &nor);
		float dn = D3DXVec3Dot(&negativeDist, &nor);

		if (dp > 0 || dn > 0)
		{
			ret = true;
		}
		else
		{
			ret = false;
			// 1�ł�false�ɂȂ������ʊO
			break;
		}
	}

	return ret;

}

/**************************************
�@�������ԋ߂��_���Z�o����
***************************************/
D3DXVECTOR3 ViewFrustum::GetPositivePoint(D3DXVECTOR3 target, const float size, D3DXVECTOR3 normal)
{
	D3DXVECTOR3 ret = target;

	if (normal.x > 0)
	{
		ret.x += size;
	}
	if (normal.y > 0)
	{
		ret.y += size;
	}
	if (normal.z > 0)
	{
		ret.z += size;
	}

	return ret;
}

/**************************************
�@�������ԉ����_���Z�o����
***************************************/
D3DXVECTOR3 ViewFrustum::GetNegativePoint(D3DXVECTOR3 target, const float size, D3DXVECTOR3 normal)
{
	D3DXVECTOR3 ret = target;

	if (normal.x < 0)
	{
		ret.x -= size;
	}
	if (normal.y < 0)
	{
		ret.y -= size;
	}
	if (normal.z < 0)
	{
		ret.z -= size;
	}

	return ret;
}
