//=====================================
//
//�A�j���[�V�����p�[�e�B�N���w�b�_[AnimationParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ANIMATIONPARTICLE_H_
#define _ANIMATIONPARTICLE_H_

#include "../../../main.h"
#include "Particle3D.h"

/**************************************
�}�N����`
***************************************/

/**************************************
AnimationParticle�N���X
���p�����Init(), Update()����������
***************************************/
class AnimationParticle3D : public Particle3D
{
	using Particle3D::Particle3D;
public:
	AnimationParticle3D(float fivX, float divY);
	AnimationParticle3D(float divX, float divY, int life);
	AnimationParticle3D(float divX, float divY, int lifeMin, int lifeMax);

	void SetAnimParameter(float texDixX, float texDivY);
	void SetAnimParameter(const D3DXVECTOR2& texDiv);

protected:
	void Animation(float t);

	int animIndexMax;
	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;
};
#endif