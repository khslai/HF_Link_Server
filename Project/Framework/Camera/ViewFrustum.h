//=====================================
//
//ViewFrustum.h
//�@�\:�J�����̎�����
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _VIEWFRUSTUM_H_
#define _VIEWFRUSTUM_H_

#include "../../main.h"
#include <vector>

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class ViewFrustum
{
public:
	//������̖ʂ�\���񋓎q
	enum Surface
	{
		Left,		//����
		Right,		//�E��
		Top,		//���
		Bottom,		//����
		Max,
	};

	//�R���X�g���N�^�A�f�X�g���N�^
	ViewFrustum();
	~ViewFrustum();

	//�ʂ̖@���擾���� �����K���ς�
	D3DXVECTOR3 GetNormal(Surface surfaceID);

	// �ʏ�̂����_���擾
	D3DXVECTOR3 GetSurfacePoint(Surface surfaceID);

	// ������J�����O
	bool CheckOnCamera(const D3DXVECTOR3 target, const float size);
	D3DXVECTOR3 GetPositivePoint(D3DXVECTOR3 target, const float size, D3DXVECTOR3 normal);
	D3DXVECTOR3 GetNegativePoint(D3DXVECTOR3 target, const float size, D3DXVECTOR3 normal);

	//���_�ݒ菈��
	void SetVertex(
		const D3DXVECTOR3& NearLeftTop, const D3DXVECTOR3& NearRightTop,
		const D3DXVECTOR3& NearLeftBottom, const D3DXVECTOR3& NearRightBottom,
		const D3DXVECTOR3& FarLeftTop, const D3DXVECTOR3& FarRightTop,
		const D3DXVECTOR3& FarLeftBottom, const D3DXVECTOR3& FarRightBottom);

private:
	//���_�ő吔
	static const unsigned VertexMax;

	//���_�R���e�i
	std::vector<D3DXVECTOR3> vertexPos;

	//�@���擾��������
	D3DXVECTOR3 _GetNormal(int v1, int v2, int v3);

	//���_�񋓎q
	enum Vertex
	{
		NearLeftTop, 
		NearRightTop,
		NearLeftBottom,
		NearRightBottom,
		FarLeftTop,
		FarRightTop,
		FarLeftBottom,
		FarRightBottom
	};

};

#endif