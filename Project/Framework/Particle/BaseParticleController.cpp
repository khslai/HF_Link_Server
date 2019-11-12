//=====================================
//
//�x�[�X�p�[�e�B�N���R���g���[������[BaseParticleController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseParticleController.h"
#include "../Tool/DebugWindow.h"
#include "../Resource/ResourceManager.h"
#include "ParticleRenderer.h"
#include "ParticleJsonParser.h"

#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
static�����o
***************************************/
shared_ptr<ParticleRenderer> BaseParticleController::mRenderer = NULL;

/**************************************
�R���X�g���N�^
***************************************/
BaseParticleController::BaseParticleController(ParticleType type) :
	unitBuff(NULL), texture(NULL), particleCount(0), useType(type)
{
	if (!mRenderer)
	{
		mRenderer.reset(new ParticleRenderer());
	}
	renderer = mRenderer;
}

/**************************************
�f�X�g���N�^
***************************************/
BaseParticleController::~BaseParticleController()
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(unitBuff);

	Utility::DeleteContainer(particleContainer);

	Utility::DeleteContainer(emitterContainer);

	renderer.reset();
}

/**************************************
�I������
***************************************/
void BaseParticleController::Uninit()
{
	for (auto& particle : particleContainer)
	{
		particle->SetActive(false);
	}

	for (auto& emitter : emitterContainer)
	{
		emitter->SetActive(false);
	}
}

/**************************************
�X�V����
***************************************/
void BaseParticleController::Update()
{
	//�G�~�b�^�X�V
	for (BaseEmitter *emitter : emitterContainer)
	{
		emitter->Update();
	}

	//�S�G�~�b�^�ɑ΂��ĕ��o����
	for (BaseEmitter* emitter : emitterContainer)
	{
		//���o����
		bool res = emitter->Emit(particleContainer);

		//���o�ł���p�[�e�B�N�����c���Ă��Ȃ����break
		if (!res)
			break;		
	}

	//�p�[�e�B�N���X�V
	for (BaseParticle *particle : particleContainer)
	{
		particle->Update();
	}
}

/**************************************
�`�揈��
***************************************/
bool BaseParticleController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�p�[�e�B�N���̃p�����[�^�𒸓_�o�b�t�@�ɃZ�b�g
	particleCount = renderer->EmbedUV(particleContainer);

	if (particleCount == 0)
		return false;

	particleCount = renderer->EmbedTransform(particleContainer);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, texture);

	//�`��
	renderer->BeginPass(useType);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);
	renderer->EndPass();

	return true;
}

/**************************************
�p�[�e�B�N���P�ʃo�b�t�@�쐬����
***************************************/
void BaseParticleController::MakeUnitBuffer(const D3DXVECTOR2& size, const D3DXVECTOR2& texDiv)
{
	if (unitBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUnit) * NUM_VERTEX, 0, 0, D3DPOOL_MANAGED, &unitBuff, 0);

	ParticleUnit *p;
	unitBuff->Lock(0, 0, (void**)&p, 0);

	//�P�ʃT�C�Y�ݒ�
	p[0].vtx = D3DXVECTOR3(-size.x / 2.0f, size.y / 2.0f, 0.0f);
	p[1].vtx = D3DXVECTOR3(size.x / 2.0f, size.y / 2.0f, 0.0f);
	p[2].vtx = D3DXVECTOR3(-size.x / 2.0f, -size.y / 2.0f, 0.0f);
	p[3].vtx = D3DXVECTOR3(size.x / 2.0f, -size.y / 2.0f, 0.0f);

	//�P��UV�ݒ�
	float u = 1.0f / texDiv.x;
	float v = 1.0f / texDiv.y;
	p[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	p[1].tex = D3DXVECTOR2(u, 0.0f);
	p[2].tex = D3DXVECTOR2(0.0f, v);
	p[3].tex = D3DXVECTOR2(u, v);

	unitBuff->Unlock();
}

/**************************************
�e�N�X�`���ǂݍ��ݏ���
***************************************/
void BaseParticleController::LoadTexture(const char* filePath)
{
	ResourceManager::Instance()->GetTexture(filePath, texture);
}

/**************************************
�G�~�b�^�R���e�i�쐬����
***************************************/
void BaseParticleController::MakeEmitterContainer(const ParticleJsonParser & data)
{
	emitterContainer.resize(data.GetEmitterMax());
	for (auto&& emitter : emitterContainer)
	{
		int emitNum = data.GetEmitNum();
		int duration = data.GetDuration();
		emitter = new BaseEmitter(emitNum, duration);
	}
}

/**************************************
�G�~�b�^�Z�b�g����
***************************************/
BaseEmitter* BaseParticleController::SetEmitter(const D3DXVECTOR3& pos, std::function<void(void)> callback)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
	{
		return !emitter->IsActive();
	});

	if (emitter == emitterContainer.end())
		return NULL;

	BaseEmitter* ptr = (*emitter);
	ptr->SetPosition(pos);
	ptr->Init(callback);

	return ptr;

}

/**************************************
�G�~�b�^�Z�b�g����
***************************************/
BaseEmitter* BaseParticleController::SetEmitter(const Transform& transform, std::function<void(void)> callback)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter *emitter)
	{
		return !emitter->IsActive();
	});

	if (emitter == emitterContainer.end())
		return NULL;

	BaseEmitter* ptr = *emitter;
	ptr->SetTransform(transform);
	ptr->Init(callback);

	return ptr;
}

/**************************************
�`��J�n����
***************************************/
void BaseParticleController::BeginDraw()
{
	mRenderer->BeginDraw();
}

/**************************************
�`��I������
***************************************/
void BaseParticleController::EndDraw()
{
	mRenderer->EndDraw();
}

/**************************************
�`��p�[�e�B�N�����擾����
***************************************/
unsigned BaseParticleController::GetParticleCount() const
{
	return particleCount;
}
