//=====================================
//
// �v���C�X�A�N�^�[[PlaceActor.cpp]
// �@�\�F�t�B�[���h��ɐݒu�����3D�I�u�W�F�N�g�p�̊��N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "PlaceActor.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Camera/ViewFrustum.h"
#include "../../Framework/Camera/Camera.h"

//**************************************
// �N���X�̃����o�ϐ�������
//**************************************
const D3DXVECTOR3 PlaceActor::Scale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//=====================================
// �R���X�g���N�^
//=====================================
PlaceActor::PlaceActor(const D3DXVECTOR3& Pos)
{
	// ���b�V���R���e�i�̍쐬
	mesh = new MeshContainer();

	// �X�e�[�^�X�Z�b�g
	transform->SetPosition(Pos);
	transform->SetScale(Scale);
	this->SetActive(true);
}

//=====================================
// �f�X�g���N�^
//=====================================
PlaceActor::~PlaceActor()
{
	SAFE_DELETE(mesh);
}

//=====================================
// �X�V
//=====================================
void PlaceActor::Update()
{
	Rotate(1.0f);

#if _DEBUG
	Debug();
#endif
}

//=====================================
// �`��
//=====================================
void PlaceActor::Draw()
{
	if (!this->IsActive())
		return;

	transform->SetWorld();
	mesh->Draw();
	//mesh->DrawWireframe(false);
}

//=====================================
// Y����]
//=====================================
void PlaceActor::Rotate(float y)
{
	transform->Rotate(0.0f, y, 0.0f);
}

//=====================================
// ���W�̃Z�b�g
//=====================================
void PlaceActor::SetPosition(const D3DXVECTOR3& Pos)
{
	transform->SetPosition(Pos);
}

//=====================================
// ���b�V���f�[�^�̃J���[�ύX
//=====================================
void PlaceActor::SetColor(const D3DXCOLOR& color)
{
	unsigned numMaterial = mesh->GetMaterialNum();

	for (unsigned i = 0; i < numMaterial; i++)
	{
		mesh->SetMaterialColor(color, i);
	}
}

//=====================================
// ���W�A��]�A�傫�������Z�b�g
//=====================================
void PlaceActor::ResetTransform()
{
	transform->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	transform->SetScale(Scale);
	transform->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=====================================
// �f�o�b�O
//=====================================
#if _DEBUG
void PlaceActor::Debug()
{

}
#endif
