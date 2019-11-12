//=====================================
//
//�g�����X�t�H�[���I�u�W�F�N�g����[TransformObject.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "TransformObject.h"
#include "../Resource/ResourceManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
TransformObject::TransformObject()
{
	ResourceManager::Instance()->LoadMesh("Transform", "data/MODEL/transform.x");
	
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh("Transform", mesh);
}

/**************************************
�f�X�g���N�^
***************************************/
TransformObject::~TransformObject()
{
	SAFE_DELETE(mesh);
}

/**************************************
�`�揈��
***************************************/
void TransformObject::Draw()
{
	transform->SetWorld();
	mesh->Draw();
}