//=====================================
//
//Particle2D.h
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

#include "../../../main.h"
#include "../BaseParticle.h"
#include "../../Core/GameObject.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class Particle2D : public BaseParticle, public GameObject
{
public:
	Particle2D();
	Particle2D(int life);
	Particle2D(int minLife, int maxLife);
	Particle2D(float u, float v, int minLife, int maxLife);
	virtual ~Particle2D();

	virtual bool IsActive() const;

	virtual void SetTransform(const Transform& transform);

	virtual void SetActive(bool state);

	virtual D3DXMATRIX GetWorldMtx();
};
#endif