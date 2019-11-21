//=====================================
//
//�J��������[Camera.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Camera.h"
#include "CameraShakePlugin.h"
#include <algorithm>

/**************************************
static�����o
***************************************/
Camera* Camera::mainCamera = NULL;

/**************************************
�R���X�g���N�^
***************************************/
Camera::Camera()
{
	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, 10.0f, 100.0f);
	const float InitViewAngle = D3DXToRadian(60.0f);
	const float InitViewAspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	const float InitViewNear = 10.0f;
	const float InitViewFar = 50000.0f;

	transform.SetPosition(InitPos);
	target = InitTarget;
	viewAngle = InitViewAngle;
	viewAspect = InitViewAspect;
	viewNear = InitViewNear;
	viewFar = InitViewFar;

	D3DXMatrixIdentity(&viewport);
	viewport._11 = SCREEN_WIDTH / 2.0f;
	viewport._22 = -SCREEN_HEIGHT / 2.0f;
	viewport._41 = SCREEN_WIDTH / 2.0f;
	viewport._42 = SCREEN_HEIGHT / 2.0f;

	upWork = transform.Up();

	//�r���[�s��쐬
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&InitPos,
		&target,
		&upWork);

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//�ϊ��s����v�Z
	VPV = view * projection * viewport;

	//�t�s����v�Z
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	Set();
}

/**************************************
�f�X�g���N�^
***************************************/
Camera::~Camera()
{
	
}

/**************************************
�X�V����
***************************************/
void Camera::Update()
{
	//�e�v���O�C���X�V
	for (auto& plugin : pluginList)
	{
		plugin->Update();
	}

	//��Ɨ̈�Ɍ��݂̃p�����[�^��ݒ�
	eyeWork = transform.GetPosition();
	targetWork = target;
	upWork = transform.Up();

	//�v���O�C�����f
	for (auto& plugin : pluginList)
	{
		plugin->Apply(*this);
	}

	//�r���[�s��쐬
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&eyeWork,
		&targetWork,
		&upWork);

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//�ϊ��s����v�Z
	VPV = view * projection * viewport;

	//�t�s����v�Z
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	//������v�Z
	CalculateFrustrum();
}

/**************************************
�Z�b�g����
***************************************/
void Camera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�s��ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &view);

	//�v���W�F�N�V�����s��ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &projection);
}

/**************************************
�v���O�C���ǉ�����
***************************************/
void Camera::AddPlugin(BaseCameraPlugin * plugin)
{
	pluginList.push_back(plugin);
}

/**************************************
�v���O�C���폜����
***************************************/
void Camera::RemovePlugin(BaseCameraPlugin *plugin)
{
	pluginList.erase(std::remove(pluginList.begin(), pluginList.end(), plugin), pluginList.end());	
}

/**************************************
���C���J�����ݒ菈��
***************************************/
void Camera::SetMainCamera(Camera * camera)
{
	mainCamera = camera;
}

/**************************************
���C���J�����擾����
***************************************/
const Camera * Camera::MainCamera()
{
	return mainCamera;
}

/**************************************
�X�N���[�����e����
***************************************/
D3DXVECTOR3 Camera::Projection(const D3DXVECTOR3& pos) const
{
	D3DXVECTOR3 out;
	D3DXVec3TransformCoord(&out, &pos, &mainCamera->VPV);
	return out;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXVECTOR3 Camera::UnProjection(const D3DXVECTOR3& pos, float z)
{
	D3DXVECTOR3 out;
	D3DXVec3TransformCoord(&out, &D3DXVECTOR3(pos.x, pos.y, z), &mainCamera->invVPV);
	return out;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetViewMtx() const
{
	return mainCamera->view;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetInverseViewMtx() const
{
	return mainCamera->invView;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetProjectionMtx() const
{
	return mainCamera->projection;
}

/**************************************
������擾����
***************************************/
ViewFrustum Camera::GetViewFrustrum() const
{
	return viewFrustrum;
}

/**************************************
������Z�o����
***************************************/
void Camera::CalculateFrustrum()
{
	const D3DXVECTOR3 LeftTop = { 0.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 RightTop = { (float)SCREEN_WIDTH, 0.0f, 0.0f };
	const D3DXVECTOR3 LeftBottom = { 0.0f, (float)SCREEN_HEIGHT, 0.0f };
	const D3DXVECTOR3 RightBottom = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f };

	viewFrustrum.SetVertex(
		UnProjection(LeftTop, 0.0f),
		UnProjection(RightTop, 0.0f),
		UnProjection(LeftBottom, 0.0f),
		UnProjection(RightBottom, 0.0f),
		UnProjection(LeftTop, 1.0f),
		UnProjection(RightTop, 1.0f),
		UnProjection(LeftBottom, 1.0f),
		UnProjection(RightBottom, 1.0f)
	);
}
