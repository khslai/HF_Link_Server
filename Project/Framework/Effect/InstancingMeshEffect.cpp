//=====================================
//
//���b�V���C���X�^���V���O�p�̃G�t�F�N�g����[InstancingMeshEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "InstancingMeshEffect.h"
#include "../Resource/ResourceManager.h"
#include "../Light/Light.h"

/**************************************
�R���X�g���N�^
***************************************/
InstancingMeshEffect::InstancingMeshEffect()
{
	//�G�t�F�N�g�ǂݍ���
	ResourceManager::Instance()->GetEffect("data/EFFECT/InstancingMesh.cfx", effect);

	//�n���h���擾
	hMtxView = effect->GetParameterByName(0, "mtxView");
	hMtxProjection = effect->GetParameterByName(0, "mtxProjection");

	hMaterialDiffuse = effect->GetParameterByName(0, "materialDiffuse");
	hMaterialAmbient = effect->GetParameterByName(0, "materialAmbient");
	hMaterialSpecular = effect->GetParameterByName(0, "materialSpecular");

	hLightDirection = effect->GetParameterByName(0, "lightDirection");
	hLightDiffuse = effect->GetParameterByName(0, "lightDiffuse");
	hLightAmbient = effect->GetParameterByName(0, "lightAmbient");
	hLightSpecular = effect->GetParameterByName(0, "lightSpecular");

	hTechnique = effect->GetTechniqueByName("tech");
	effect->SetTechnique(hTechnique);
}

/**************************************
�f�X�g���N�^
***************************************/
InstancingMeshEffect::~InstancingMeshEffect()
{
	SAFE_RELEASE(effect);
}

/**************************************
���C�g�ƃJ�����̕ύX���f����
***************************************/
void InstancingMeshEffect::CommitCameraParameter()
{
	//�r���[�A�v���W�F�N�V�����s��ݒ�
	effect->SetMatrix(hMtxView, &mtxView);
	effect->SetMatrix(hMtxProjection, &mtxProjection);

	//���C�g���擾
	int numLight = Light::LightMax();
	std::vector<D3DLIGHT9> light(numLight);
	for (int i = 0; i < numLight; i++)
	{
		light[i] = Light::GetData(i);
	}

	//��Ɨ̈�
	std::vector<D3DXVECTOR4> workDir(numLight);
	std::vector<D3DCOLORVALUE> workColor(numLight);

	//���C�g�����ݒ�
	for (int i = 0; i < numLight; i++)
	{
		workDir[i] = D3DXVECTOR4(light[i].Direction, 0.0f);
	}
	effect->SetVectorArray(hLightDirection, &workDir[0], numLight);

	//���C�g�g�U���ݒ�
	for (int i = 0; i < numLight; i++)
	{
		workColor[i] = light[i].Diffuse;
	}
	effect->SetVectorArray(hLightDiffuse, (D3DXVECTOR4*)&workColor[0], numLight);

	//���C�g�����ݒ�
	for (int i = 0; i < numLight; i++)
	{
		workColor[i] = light[i].Ambient;
	}
	effect->SetVectorArray(hLightAmbient, (D3DXVECTOR4*)&workColor[0], numLight);
}

/**************************************
�}�e���A���Z�b�g����
***************************************/
void InstancingMeshEffect::SetMaterial(const D3DMATERIAL9 & material)
{
	effect->SetFloatArray(hMaterialDiffuse, (float*)&material.Diffuse, 4);
	effect->SetFloatArray(hMaterialAmbient, (float*)&material.Ambient, 4);
	effect->SetFloatArray(hMaterialSpecular, (float*)&material.Specular, 4);
}
