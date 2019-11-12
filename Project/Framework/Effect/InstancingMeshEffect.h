//=====================================
//
// InstancingMeshEffect.h
// �@�\:���b�V���C���X�^���V���O�p�G�t�F�N�g
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _INSTANCINGMESHEFFECT_H_
#define _INSTANCINGMESHEFFECT_H_

#include "../../main.h"
#include "RendererEffect.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class InstancingMeshEffect : public RendererEffect
{
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	InstancingMeshEffect();
	~InstancingMeshEffect();

	void CommitCameraParameter();

	//�}�e���A���ݒ菈��
	void SetMaterial(const D3DMATERIAL9& material);

private:
	//�V�F�[�_�ւ̃n���h��
	D3DXHANDLE hMtxView;
	D3DXHANDLE hMtxProjection;
	
	D3DXHANDLE hMaterialDiffuse;
	D3DXHANDLE hMaterialAmbient;
	D3DXHANDLE hMaterialSpecular;

	D3DXHANDLE hLightDirection;
	D3DXHANDLE hLightDiffuse;
	D3DXHANDLE hLightAmbient;
	D3DXHANDLE hLightSpecular;

	D3DXHANDLE hTechnique;
};

#endif