//=============================================================================
//
// �w�i�N���X [Transition.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _Transition_H_
#define _Transition_H_

#include "../../Framework/PostEffect/ScreenObject.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Transition : public ScreenObject
{
private:
	bool Active;
	int CountFrame;
	D3DXVECTOR3 Color;
	LPDIRECT3DTEXTURE9 Texture;
	LPD3DXEFFECT effect;					//�V�F�[�_�G�t�F�N�g
	D3DXHANDLE hFlashColor;					//�V�F�[�_�ւ̃n���h��

public:
	Transition();
	~Transition();
	void Update(void);
	void Draw(void);
	void LoadTexture(const LPDIRECT3DTEXTURE9& Texture);
	void SetTransition(void);
	bool InActive(void) { return this->Active; };
};

#endif
