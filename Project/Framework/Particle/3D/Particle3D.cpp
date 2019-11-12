//=====================================
//
//Particle3D.cpp
//�@�\:�p�[�e�B�N��3D
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Particle3D.h"

/**************************************
�R���X�g���N�^
***************************************/
Particle3D::Particle3D()
{
}

/**************************************
�R���X�g���N�^
***************************************/
Particle3D::Particle3D(int life) :
	BaseParticle(life),
	BillboardObject(false)
{
}

/**************************************
�R���X�g���N�^
***************************************/
Particle3D::Particle3D(int minLife, int maxLife) :
	BaseParticle(minLife, maxLife),
	BillboardObject(false)
{
}

/**************************************
�R���X�g���N�^
***************************************/
Particle3D::Particle3D(float u, float v, int minLife, int maxLife) :
	BaseParticle(u, v, minLife, maxLife),
	BillboardObject(false)
{
}

/**************************************
�f�X�g���N�^
***************************************/
Particle3D::~Particle3D()
{
}

/**************************************
�A�N�e�B�u����
***************************************/
bool Particle3D::IsActive() const
{
	if (!active)
		return false;

	return _IsActive();
}

/**************************************
�g�����X�t�H�[���ݒ菈��
***************************************/
void Particle3D::SetTransform(const Transform& transform)
{
	BillboardObject::SetTransform(transform);
}

/**************************************
�A�N�e�B�u�Z�b�g����
***************************************/
void Particle3D::SetActive(bool state)
{
	BillboardObject::SetActive(state);
}

/**************************************
���[���h�ϊ��s��擾����
***************************************/
D3DXMATRIX Particle3D::GetWorldMtx()
{
	return transform->GetMatrix();
}
