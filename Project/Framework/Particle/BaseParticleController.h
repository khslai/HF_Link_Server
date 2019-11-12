//=====================================
//
//�x�[�X�p�[�e�B�N���R���g���[���w�b�_[BaseParticleController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEPARTICLECONTROLLER_H_
#define _BASEPARTICLECONTROLLER_H_

#include "../../main.h"
#include "BaseParticle.h"
#include "BaseEmitter.h"
#include "ParticleJsonParser.h"
#include "ParticleRenderer.h"

#include <vector>
#include <functional>

/**************************************
�}�N����`
***************************************/

/**************************************
�O���錾
***************************************/
class ParticleRenderer;
class ParticleUnit;

/**************************************
BasePartlceController�N���X
�p�����
�E�P�ʒ��_�o�b�t�@�쐬�A�e�N�X�`���ǂݍ���
�Evoid MakeParticleContainer(), MakeEmitterContainer()
����������
***************************************/
class BaseParticleController
{
public:
	enum ParticleType
	{
		Particle_3D = 0,
		Particle_2D,
		Max
	};

	//�R���X�g���N�^�A�f�X�g���N�^
	BaseParticleController(ParticleType type);
	virtual ~BaseParticleController();

	template<class T>
	BaseParticleController(const T& src, const ParticleJsonParser& data) :
		unitBuff(NULL), texture(NULL)
	{
		if (!mRenderer)
		{
			mRenderer.reset(new ParticleRenderer());
		}
		renderer = mRenderer;

		//�e�N�X�`�����[�h
		LoadTexture(data.GetTexturePath().c_str());

		//�P�ʒ��_�o�b�t�@�쐬
		MakeUnitBuffer(data.GetSize(), data.GetTexDiv());

		//�p�[�e�B�N���R���e�i�쐬
		particleContainer.resize(data.GetParticleMax());
		for (auto&& particle : particleContainer)
		{
			particle = new T();
		}

		//�G�~�b�^�R���e�i�쐬
		MakeEmitterContainer(data);

	};

	//�G�~�b�^�Z�b�g����
	virtual BaseEmitter* SetEmitter(const D3DXVECTOR3& pos, std::function<void(void)> callback = nullptr);
	virtual BaseEmitter* SetEmitter(const Transform& transform, std::function<void(void)> callback = nullptr);

	virtual void Uninit();				//�I������
	virtual void Update();				//�X�V����
	virtual bool Draw();				//�`�揈��

	//�`��J�n�E�I������
	static void BeginDraw();
	static void EndDraw();

	//�`��p�[�e�B�N�����擾����
	unsigned GetParticleCount() const;

protected:
	LPDIRECT3DVERTEXBUFFER9 unitBuff;				//�P�ʒ��_�o�b�t�@
	LPDIRECT3DTEXTURE9 texture;						//�e�N�X�`��
	std::vector<BaseParticle*> particleContainer;	//�p�[�e�B�N���R���e�i
	std::vector<BaseEmitter*> emitterContainer;		//�G�~�b�^�R���e�i
	std::shared_ptr<ParticleRenderer> renderer;		//�����_���[

	unsigned particleCount;							//�`��p�[�e�B�N����

	//�P�ʒ��_�o�b�t�@�쐬����
	void MakeUnitBuffer(const D3DXVECTOR2& size, const D3DXVECTOR2& texDix = D3DXVECTOR2(1.0f, 1.0f));	
	void LoadTexture(const char* filePath);			//�e�N�X�`���ǂݍ��ݏ���

	//�R���e�i�쐬
	virtual void MakeEmitterContainer(const ParticleJsonParser& data);

	//�g�p����p�[�e�B�N���̃^�C�v
	ParticleType useType;

private:
	//�C���X�^���V���O�ɕK�v�ȐÓI�����o
	static std::shared_ptr<ParticleRenderer> mRenderer;
};

/**************************************
�p�[�e�B�N���̒P�ʒ��_
***************************************/
class ParticleUnit
{
public:
	D3DXVECTOR3 vtx;	//���_���W
	D3DXVECTOR2 tex;	//UV���W
};

#endif