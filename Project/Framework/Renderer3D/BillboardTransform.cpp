//=====================================
//
//�r���{�[�h�g�����X�t�H�[������[BillboardTransform.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BillboardTransform.h"
#include "../Camera/Camera.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
void BillboardTransform::SetWorld(const D3DXMATRIX * parent) const
{
	D3DXMATRIX world, rotation, view, invView;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//��]
	D3DXMatrixRotationQuaternion(&world, &this->rotation);

	//�r���{�[�h����
	pDevice->GetTransform(D3DTS_VIEW, &view);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;
	D3DXMatrixMultiply(&world, &world, &invView);

	//�X�P�[��
	world._11 *= scale.x;
	world._12 *= scale.x;
	world._13 *= scale.x;

	world._21 *= scale.y;
	world._22 *= scale.y;
	world._23 *= scale.y;

	world._31 *= scale.z;
	world._32 *= scale.z;
	world._33 *= scale.z;

	//�ړ�
	world._41 = position.x;
	world._42 = position.y;
	world._43 = position.z;

	//�e�𔽉f
	if (parent != NULL)
	{
		D3DXMatrixMultiply(&world, parent, &world);
	}

	pDevice->SetTransform(D3DTS_WORLD, &world);
}

/**************************************
�O���[�o���ϐ�
***************************************/
D3DXMATRIX BillboardTransform::GetMatrix() const
{
	/*************************************
	NOTE:�����ɍs��v�Z������A�v�f�𒼐ڌv�Z�����������������̂�
	��]�����s��ŁA����ȊO�͒��ڌv�Z���Ă���
	*************************************/
	D3DXMATRIX world;

	//��]
	D3DXMatrixRotationQuaternion(&world, &this->rotation);

	////�r���{�[�h����
	D3DXMATRIX invView = Camera::MainCamera()->GetInverseViewMtx();
	invView._41 = invView._42 = invView._43 = 0.0f;
	D3DXMatrixMultiply(&world, &world, &invView);

	//�X�P�[��
	world._11 *= scale.x;
	world._12 *= scale.x;
	world._13 *= scale.x;

	world._21 *= scale.y;
	world._22 *= scale.y;
	world._23 *= scale.y;

	world._31 *= scale.z;
	world._32 *= scale.z;
	world._33 *= scale.z;

	//�ړ�
	world._41 = position.x;
	world._42 = position.y;
	world._43 = position.z;

	return world;
}
