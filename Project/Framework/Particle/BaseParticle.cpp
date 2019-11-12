//=====================================
//
//�x�[�X�p�[�e�B�N������[BaseParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseParticle.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle() :
	uv(ParticleUV())
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle(int life) :
	uv(ParticleUV()),
	lifeFrame(life)
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle(int lifeMin, int lifeMax) :
	uv(ParticleUV()),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax))
{

}

/**************************************
�R���X�g���N�^
***************************************/
BaseParticle::BaseParticle(float u, float v, int lifeMin, int lifeMax) :
	uv(ParticleUV(u, v)),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax))
{
}

/**************************************
�f�X�g���N�^
***************************************/
BaseParticle::~BaseParticle()
{
}

/**************************************
�A�N�e�B�u����
***************************************/
bool BaseParticle::_IsActive() const
{
	return cntFrame <= lifeFrame;
}
