//=====================================
//
//�x�[�X�p�[�e�B�N���w�b�_[BaseParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEPARTICLE_H_
#define _BASEPARTICLE_H_

#include "../../main.h"
#include "../Renderer3D/BillboardObject.h"

/**************************************
�O���錾
***************************************/

/**************************************
�p�[�e�B�N����UV���W
***************************************/
class ParticleUV
{
public:
	float u, v;

	ParticleUV() :
		u(0.0f),
		v(0.0f)
	{

	}

	ParticleUV(float u, float v) :
		u(u),
		v(v)
	{

	}
};

/**************************************
BaseParticle�N���X
���p�����Init(), Update()����������
***************************************/
class BaseParticle
{
public:
	BaseParticle();
	BaseParticle(int life);
	BaseParticle(int lifeMin, int lifeMax);
	BaseParticle(float u, float v, int lifeMin, int lifeMax);
	virtual ~BaseParticle();

	virtual void Init() = 0;
	virtual void Update() = 0;

	virtual bool IsActive() const = 0;

	virtual void SetTransform(const Transform& transform) = 0;

	virtual void SetActive(bool state) = 0;

	virtual D3DXMATRIX GetWorldMtx() = 0;

	ParticleUV uv;

protected:
	int cntFrame;
	int lifeFrame;

	bool _IsActive() const;
};

#endif