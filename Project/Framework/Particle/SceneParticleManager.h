//=====================================
//
//�V�[���p�[�e�B�N���}�l�[�W���w�b�_[SceneParticleManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCENEPARTICLEMANAGER_H_
#define _SCENEPARTICLEMANAGER_H_

#include "../../main.h"

#include <vector>
#include <functional>

/**************************************
�O���錾
***************************************/
class CrossFilterController;
class ScreenObject;
class BaseParticleController;
class BaseEmitter;

/**************************************
�N���X��`
***************************************/
class SceneParticleManager
{
public:
	SceneParticleManager();

	//�������A�I���A�X�V�A�`�揈��
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	//�p�[�e�B�N����������
	virtual BaseEmitter* Generate(UINT id, const D3DXVECTOR3& pos, std::function<void(void)> callback = nullptr);
	virtual BaseEmitter* Generate(UINT id, const Transform& transform, std::function<void(void)> callback = nullptr);

protected:
	//�����_�[�^�[�Q�b�g�֘A
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
	D3DVIEWPORT9 viewPort;
	ScreenObject *screenObj;

	//�L���b�V���p
	LPDIRECT3DSURFACE9 oldSuf;
	D3DVIEWPORT9 oldViewport;

	//�p�[�e�B�N���R���g���[���R���e�i
	std::vector<BaseParticleController*> controllers;

	//�N���X�t�B���^
	CrossFilterController *crossFilter;

	//�`�揀��
	void CreateRenderTarget(void);
	void ChangeRenderParameter(void);
	void RestoreRenderParameter(void);

private:
	bool initialized;
};
#endif