//=====================================
//
// �C�x���g�A�N�^�[���N���X[EventActorBase.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#include "EventActorBase.h"
#include "../Framework/Resource/ResourceManager.h"

//=====================================
// �R���X�g���N�^
//=====================================
EventActorBase::EventActorBase(D3DXVECTOR3 Pos, D3DXVECTOR3 Scale, const char* MeshTag)
{
	// ���b�V���R���e�i�̍쐬
	mesh = new MeshContainer();
	ResourceManager::Instance()->GetMesh(MeshTag, mesh);

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(Pos);
	transform->SetScale(Scale);
	SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
EventActorBase::~EventActorBase()
{
	SAFE_DELETE(mesh);
}

//=====================================
// �X�V
//=====================================
void EventActorBase::Update()
{
}

//=====================================
// �`��
//=====================================
void EventActorBase::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
}