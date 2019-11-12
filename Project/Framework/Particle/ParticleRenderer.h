//=====================================
//
//�p�[�e�B�N�������_���[�w�b�_[ParticleRenderer.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PARTICLERENDERER_H_
#define _PARTICLERENDERER_H_

#include "../../main.h"
#include <vector>

/**************************************
�}�N����`
***************************************/
#define PARTICLE_NUM_MAX	(2048)

/**************************************
�O���錾
***************************************/
class BaseParticle;

/**************************************
�N���X��`
***************************************/
class ParticleRenderer
{
public:
	ParticleRenderer();
	~ParticleRenderer();

	void BeginDraw();
	void EndDraw();

	void BeginPass(DWORD pass);
	void EndPass();

	UINT EmbedTransform(const std::vector<BaseParticle*> container);
	UINT EmbedUV(const std::vector<BaseParticle*> container);

private:
	LPDIRECT3DVERTEXDECLARATION9 declare;
	LPD3DXEFFECT effect;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	LPDIRECT3DVERTEXBUFFER9 transformBuff, uvBuff;
	D3DXHANDLE hMtxView, hMtxProjection, hMtxInvView, hScreenProj;

	void LoadEffect();
	void MakeDeclaration();
	void MakeTransformBuffer();
	void MakeUVBuffer();
	void MakeIndexBuffer();
};

#endif