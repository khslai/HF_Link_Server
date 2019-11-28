//=====================================
//
// �|���S���`��N���X[PolygonDrawer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=====================================
#ifndef _PolygonDrawer_H_
#define _PolygonDrawer_H_

#include "../../../Framework/Renderer3D/BoardPolygon.h"

enum MovePolygonType
{
	Wall,
	Ground,
	Max
};


/**************************************
�N���X��`
***************************************/
class PolygonDrawer : public BoardPolygon
{
private:
	D3DXVECTOR3 Pos;		// �|���S���̌��ݍ��W
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 Scale;
	D3DXVECTOR3 DestPos;	// �ړ��̖ڕW���W
	D3DXVECTOR3 StartPos;	// �������W
	bool Movable;			// �ړ��t���O
	float MoveSpeed;

	void SetPolygonPara(const char* Tag, int Num);

public:
	//�R���X�g���N�^�A�f�X�g���N�^
	PolygonDrawer(const char* Tag, D3DXVECTOR3 Pos);
	PolygonDrawer(const char* Tag, D3DXVECTOR3 StartPos, D3DXVECTOR3 DestPos);
	PolygonDrawer(const char* Tag, D3DXVECTOR3 StartPos, D3DXVECTOR3 DestPos, int Num);
	~PolygonDrawer();

	// �X�V����
	void Update(void);
	// �`�揈��
	void Draw(void);
	// �e�N�X�`���ʂ��ԍ��ݒ菈��
	void SetTextureIndex(int index);
	void SetPosition(const D3DXVECTOR3& Pos);
	void SetRotation(const D3DXVECTOR3& Rot);
	void SetFade(D3DXMATRIX& WorldMatrix);
};

#endif