//=====================================
//
//AnimationParticle2D.h
//�@�\:�A�j���[�V�����p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ANIMATIONPARTICLE2D_H_
#define _ANIMATIONPARTICLE2D_H_

#include "../../../main.h"
#include "Particle2D.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class AnimationParticle2D : public Particle2D
{
	using Particle2D::Particle2D;
public:
	AnimationParticle2D(float fivX, float divY);
	AnimationParticle2D(float divX, float divY, int life);
	AnimationParticle2D(float divX, float divY, int lifeMin, int lifeMax);

	void SetAnimParameter(float texDixX, float texDivY);
	void SetAnimParameter(const D3DXVECTOR2& texDiv);

protected:
	void Animation(float t);

	int animIndexMax;
	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;
};
#endif