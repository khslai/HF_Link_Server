//=============================================================================
//
// 背景クラス [Transition.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _Transition_H_
#define _Transition_H_

#include "../../Framework/PostEffect/ScreenObject.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Transition : public ScreenObject
{
private:
	bool Active;
	int CountFrame;
	D3DXVECTOR3 Color;
	LPDIRECT3DTEXTURE9 Texture;
	LPD3DXEFFECT effect;					//シェーダエフェクト
	D3DXHANDLE hFlashColor;					//シェーダへのハンドル

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
