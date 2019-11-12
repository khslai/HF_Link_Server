//=====================================
//
// �V�e�B�A�N�^�[[CityActor.cpp]
// �@�\�F�s�s�i���A���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "CityActor.h"
#include "../../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
CityActor::CityActor(const D3DXVECTOR3& Pos) :
	PlaceActor(Pos)
{
	// ���f���f�[�^�Q��
	ResourceManager::Instance()->GetMesh("Town-City", mesh);
	mesh->SetWireframePara();
	//ResourceManager::Instance()->GetMesh("Town-Space", mesh);

	type = Field::Model::Town;
}

//=====================================
// �f�X�g���N�^
//=====================================
CityActor::~CityActor()
{
}
