//=====================================
//
//Particle2D.cpp
//�@�\:2D�p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Particle2D.h"

/**************************************
�R���X�g���N�^
***************************************/
Particle2D::Particle2D() :
	BaseParticle(),
	GameObject(false)
{
}

/**************************************
�R���X�g���N�^
***************************************/
Particle2D::Particle2D(int life) :
	BaseParticle(life),
	GameObject(false)
{
}

/**************************************
�R���X�g���N�^
***************************************/
Particle2D::Particle2D(int minLife, int maxLife) :
	BaseParticle(minLife, maxLife),
	GameObject(false)
{
}

/**************************************
�R���X�g���N�^
***************************************/
Particle2D::Particle2D(float u, float v, int minLife, int maxLife) :
	BaseParticle(u, v, minLife, maxLife),
	GameObject(false)
{
}

/**************************************
�f�X�g���N�^
***************************************/
Particle2D::~Particle2D()
{
}

/**************************************
�R���X�g���N�^
***************************************/
bool Particle2D::IsActive() const
{
	if (!active)
		return false;

	return _IsActive();
}

/**************************************
�g�����X�t�H�[���ݒ菈��
***************************************/
void Particle2D::SetTransform(const Transform & transform)
{
	GameObject::SetTransform(transform);
}

/**************************************
�A�N�e�B�u�Z�b�g����
***************************************/
void Particle2D::SetActive(bool state)
{
	GameObject::SetActive(state);
}

/**************************************
���[���h�ϊ��s��擾����
***************************************/
D3DXMATRIX Particle2D::GetWorldMtx()
{
	return transform->GetMatrix();
}
