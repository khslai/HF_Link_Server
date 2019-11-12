//=====================================
//
//AnimationParticle2D.cpp
//�@�\:�A�j���[�V�����p�[�e�B�N��2D
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "AnimationParticle2D.h"

/**************************************
�R���X�g���N�^
***************************************/
AnimationParticle2D::AnimationParticle2D(float divX, float divY) :
	Particle2D()
{
	SetAnimParameter(divX, divY);
}

/**************************************
�R���X�g���N�^
***************************************/
AnimationParticle2D::AnimationParticle2D(float divX, float divY, int life) :
	Particle2D(life)
{
	SetAnimParameter(divX, divY);
};

/**************************************
�R���X�g���N�^
***************************************/
AnimationParticle2D::AnimationParticle2D(float divX, float divY, int lifeMin, int lifeMax) :
	Particle2D(lifeMin, lifeMax)
{
	SetAnimParameter(divX, divY);
}

/**************************************
�A�j���[�V��������
***************************************/
void AnimationParticle2D::Animation(float t)
{
	int animIndex = (int)(t * animIndexMax);

	int x = animIndex % (int)texDiv.x;
	int y = animIndex / (int)texDiv.x;

	uv.u = x * texSize.x;
	uv.v = y * texSize.y;
}

/**************************************
�A�j���[�V�����p�����[�^�Z�b�g����
***************************************/
void AnimationParticle2D::SetAnimParameter(float divX, float divY)
{
	texDiv = D3DXVECTOR2(divX, divY);
	texSize.x = 1.0f / divX;
	texSize.y = 1.0f / divY;

	animIndexMax = (int)(divX * divY) - 1;
}

/**************************************
�A�j���[�V�����p�����[�^�Z�b�g����
***************************************/
void AnimationParticle2D::SetAnimParameter(const D3DXVECTOR2& texDiv)
{
	this->texDiv = texDiv;
	texSize.x = 1.0f / texDiv.x;
	texSize.y = 1.0f / texDiv.y;

	animIndexMax = (int)(texDiv.x * texDiv.y) - 1;
}