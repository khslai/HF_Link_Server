//=====================================
//
//�J�����w�b�_[Camera.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../main.h"
#include "ViewFrustum.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class BaseCameraPlugin;
class SpriteEffect;

/**************************************
Camera�N���X
***************************************/
class Camera
{
	friend class BaseGame;
public:
	Camera();					//�R���X�g���N�^
	virtual ~Camera();			//�f�X�g���N�^

	virtual void Update();		//�X�V
	virtual void Set();			//�J������񔽉f����

	//�v���O�C���ǉ�����
	virtual void AddPlugin(BaseCameraPlugin* plugin);
	virtual void RemovePlugin(BaseCameraPlugin* plugin);

	//���C���J�����Z�b�g�A�Q�b�g����
	static void SetMainCamera(Camera* camera);
	static const Camera* MainCamera();

	//�^�������[���h���W���X�N���[�����W�ɕϊ�����֐�
	D3DXVECTOR3 Projection(const D3DXVECTOR3& pos) const;

	//�^�����X�N���[�����W�����[���h���W�ɕϊ�����֐�
	D3DXVECTOR3 UnProjection(const D3DXVECTOR3& pos, float z) const;

	//�r���[�s��擾����
	D3DXMATRIX GetViewMtx() const;

	//�r���[�t�s��擾����
	D3DXMATRIX GetInverseViewMtx() const;

	//�v���W�F�N�V�����s��擾����
	D3DXMATRIX GetProjectionMtx() const;

	//������擾����
	ViewFrustum GetViewFrustrum() const;

protected:
	//SRT���
	Transform transform;

	//�����_
	D3DXVECTOR3 target;

	//���_�A�����_�A������i��Ɨp�̈�j
	D3DXVECTOR3 eyeWork;
	D3DXVECTOR3 targetWork;
	D3DXVECTOR3 upWork;

	//����p�A�A�X�y�N�g��A�j�A�l�A�t�@�[�l
	float viewAngle;
	float viewAspect;
	float viewNear;
	float viewFar;

	//������
	ViewFrustum viewFrustrum;

	//�r���[�A�v���W�F�N�V�����s��A�r���[�|�[�g�s��
	D3DXMATRIX view, projection, viewport;
	D3DXMATRIX VPV;

	//�r���[�A�v���W�F�N�V�����A�r���[�|�[�g�t�s��
	D3DXMATRIX invView, invProjection, intViewport;
	D3DXMATRIX invVPV;

	//�v���O�C�����X�g
	std::vector<BaseCameraPlugin*> pluginList;
	
	//�Q�[���ɃZ�b�g�����J�����̃C���X�^���X
	static Camera* mainCamera;

	//������v�Z����
	void CalculateFrustrum();

public:
	class ShakePlugin;				//�J������h�炷�v���O�C��
	class TranslationPlugin;		//�J�������w�肵���ʒu�ɕ��s�ړ�������v���O�C��
	
};

/**************************************
�J�����v���O�C�����N���X
***************************************/
class BaseCameraPlugin
{
public:
	virtual void Update() = 0;
	virtual void Apply(Camera& camera) = 0;
};

#endif