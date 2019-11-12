//=====================================
//
//Light.cpp
//�@�\:���C�g
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Light.h"

namespace Light
{
	/**************************************
	�O���[�o���ϐ�
	***************************************/
	static D3DLIGHT9 light[NUM_LIGHT];
	static int NumLigt = 3;

	/**************************************
	����������
	***************************************/
	void Init()
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXVECTOR3 vecDir;
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&light[0], sizeof(D3DLIGHT9));
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&light[2], sizeof(D3DLIGHT9));
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&light[1], sizeof(D3DLIGHT9));

		// ���C�g0�̐ݒ�
		light[0].Type = D3DLIGHT_DIRECTIONAL;
		light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		light[0].Ambient = D3DXCOLOR(0.1f, 0.1f, 0.5f, 1.0f);
		vecDir = D3DXVECTOR3(0.80f, -1.0f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[0].Direction, &vecDir);

		// ���C�g1�̐ݒ�
		light[1].Type = D3DLIGHT_DIRECTIONAL;
		light[1].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		light[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		vecDir = D3DXVECTOR3(-0.0f, 1.00f, -0.50f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[1].Direction, &vecDir);

		// ���C�g2�̐ݒ�
		light[2].Type = D3DLIGHT_DIRECTIONAL;
		light[2].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		light[2].Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		vecDir = D3DXVECTOR3(-0.40f, -0.5f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light[2].Direction, &vecDir);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(0, &light[0]);
		pDevice->LightEnable(0, TRUE);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(1, &light[1]);
		pDevice->LightEnable(1, TRUE);

		// ���C�g�������_�����O�p�C�v���C���ɐݒ�
		pDevice->SetLight(2, &light[2]);
		pDevice->LightEnable(2, TRUE);

		// ���C�e�B���O���[�h
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	/**************************************
	���C�g���擾����
	***************************************/
	D3DLIGHT9 GetData(int id)
	{
		if (id >= NUM_LIGHT)
			return D3DLIGHT9();
		else
			return light[id];
	}

	/**************************************	
	���C�g���擾����
	***************************************/
	int LightMax()
	{
		return NumLigt;
	}

}
