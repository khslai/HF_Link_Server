//=====================================
//
//�p�[�e�B�N�������_���[����[ParticleRenderer.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "ParticleRenderer.h"
#include "BaseParticle.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ParticleRenderer::ParticleRenderer() :
	declare(NULL), effect(NULL),indexBuff(NULL), transformBuff(NULL), uvBuff(NULL),
	hMtxInvView(NULL), hMtxProjection(NULL), hMtxView(NULL)
{
	MakeDeclaration();
	MakeTransformBuffer();
	MakeUVBuffer();
	MakeIndexBuffer();
	LoadEffect();
}

/**************************************
�f�X�g���N�^
***************************************/
ParticleRenderer::~ParticleRenderer()
{
	SAFE_RELEASE(declare);
	SAFE_RELEASE(effect);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(transformBuff);
	SAFE_RELEASE(uvBuff);
}

/**************************************
�`��J�n����
***************************************/
void ParticleRenderer::BeginDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�X�e�[�g�؂�ւ�
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//�r���[�s��A�v���W�F�N�V�����s��A�r���[�t�s����擾
	D3DXMATRIX view, proj, invView, screenProj;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;

	D3DXMatrixIdentity(&screenProj);
	screenProj._11 = 2.0f / SCREEN_WIDTH;
	screenProj._22 = -2.0f / SCREEN_HEIGHT;
	screenProj._41 = -1;
	screenProj._42 = 1;

	//�V�F�[�_�Ɋe�s���ݒ�
	effect->SetMatrix(hMtxView, &view);
	effect->SetMatrix(hMtxProjection, &proj);
	effect->SetMatrix(hMtxInvView, &invView);
	effect->SetMatrix(hScreenProj, &screenProj);

	//�e���_�o�b�t�@��ݒ�
	pDevice->SetStreamSource(1, transformBuff, 0, sizeof(D3DXMATRIX));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(ParticleUV));
	pDevice->SetIndices(indexBuff);
	pDevice->SetVertexDeclaration(declare);

	//�X�g���[�����g���ݒ�
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�V�F�[�_�ɂ��`��J�n
	effect->Begin(0, 0);
}

/**************************************
�`��I������
***************************************/
void ParticleRenderer::EndDraw()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�V�F�[�_�ɂ��`��I��
	effect->End();

	//�����_�[�X�e�[�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//�X�g���[�����g������
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
Transform��񖄂ߍ��ݏ���
***************************************/
void ParticleRenderer::BeginPass(DWORD pass)
{
	effect->BeginPass(pass);
}

/**************************************
Transform��񖄂ߍ��ݏ���
***************************************/
void ParticleRenderer::EndPass()
{
	effect->EndPass();
}

/**************************************
Transform��񖄂ߍ��ݏ���
***************************************/
UINT ParticleRenderer::EmbedTransform(const std::vector<BaseParticle*> container)
{
	assert(container.size() <= PARTICLE_NUM_MAX);

	UINT count = 0;
	D3DXMATRIX *pTr;
	transformBuff->Lock(0, 0, (void**)&pTr, 0);
	for (BaseParticle *particle : container)
	{
		if (!particle->IsActive())
			continue;

		*pTr = particle->GetWorldMtx();
		pTr++;
		count++;
	}
	transformBuff->Unlock();

	return count;
}

/**************************************
UV��񖄂ߍ��ݏ���
***************************************/
UINT ParticleRenderer::EmbedUV(const std::vector<BaseParticle*> container)
{
	assert(container.size() <= PARTICLE_NUM_MAX);

	UINT count = 0;
	ParticleUV *pUV;
	uvBuff->Lock(0, 0, (void**)&pUV, 0);
	for (BaseParticle *particle : container)
	{
		if (!particle->IsActive())
			continue;

		*pUV = particle->uv;
		pUV++;
		count++;
	}
	transformBuff->Unlock();

	return count;
}

/**************************************
�G�t�F�N�g�ǂݍ��ݏ���
***************************************/
void ParticleRenderer::LoadEffect()
{
	if (effect != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, "data/EFFECT/particle3D.cfx", 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	hMtxView = effect->GetParameterByName(NULL, "mtxView");
	hMtxProjection = effect->GetParameterByName(NULL, "mtxProj");
	hMtxInvView = effect->GetParameterByName(NULL, "mtxInvView");
	hScreenProj = effect->GetParameterByName(NULL, "mtxScreenProj");
}

/**************************************
���_�錾�쐬����
***************************************/
void ParticleRenderer::MakeDeclaration()
{
	if (declare != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVERTEXELEMENT9 elems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//�P�ʒ��_�i���_���W�j
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//�P�ʒ��_�i�e�N�X�`�����W�j
		{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	//���[���h�ϊ��s��1�s�ځj
		{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	//���[���h�ϊ����2�s��
		{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	//���[���h�ϊ����3�s��
		{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },	//���[���h�ϊ����4�s��
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 5 },	//�ʂ̃e�N�X�`��
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(elems, &declare);
}

/**************************************
�g�����X�t�H�[���o�b�t�@�쐬����
***************************************/
void ParticleRenderer::MakeTransformBuffer()
{
	if (transformBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &transformBuff, 0);
}

/**************************************
UV�o�b�t�@�쐬����
***************************************/
void ParticleRenderer::MakeUVBuffer()
{
	if (uvBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUV) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &uvBuff, 0);
}

/**************************************
�C���f�b�N�X�o�b�t�@�쐬����
***************************************/
void ParticleRenderer::MakeIndexBuffer()
{
	if (indexBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	WORD index[] = { 0, 1, 2, 2, 1, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);

	void* p;
	indexBuff->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuff->Unlock();
}