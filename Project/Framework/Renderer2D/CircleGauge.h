//=====================================
//
//CircleGauge.h
//�@�\:�~�`�Q�[�W
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CIRCLEGAUGE_H_
#define _CIRCLEGAUGE_H_

#include "../../main.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class CircleGauge
{
public:
	//�ǂ����Q�[�W�̎n�_�ɂ��邩
	enum FillStart
	{
		Right,		//�E�[
		Top,		//��[
		Left,		//���[
		Bottom		//���[
	};

	//�R���X�g���N�^�A�f�X�g���N�^
	CircleGauge(const D3DXVECTOR2& Size);
	~CircleGauge();

	//�`�揈��
	void Draw();

	//�e�N�X�`���ǂݍ��ݏ���
	void LoadTexture(const char* path);

	//SRT���ݒ菈��
	void SetPosition(const D3DXVECTOR3& pos);
	void SetRotation(const D3DXVECTOR3& rot);	//���W�A���ł͂Ȃ��p�x�����̂܂ܓn��
	void SetScale(const D3DXVECTOR3& scale);

	//�p�[�Z���g�ݒ菈��(0.0 ~ 1.0)
	void SetPercent(float per);

	//�n�_�ݒ菈��
	void SetFillStart(FillStart start);

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;		//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 texture;				//�e�N�X�`��

	Transform* transform;					//SRT���

	LPD3DXEFFECT effect;					//�G�t�F�N�g

	float percent;							//�Q�[�W�̕\��%
	FillStart start;						//�Q�[�W�̎n�_

	//�V�F�[�_�̃O���[�o���ϐ��ւ̃n���h��
	D3DXHANDLE hPercent;
	D3DXHANDLE hMatrix;
	D3DXHANDLE hProj;
};

#endif