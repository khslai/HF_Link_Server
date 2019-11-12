//=====================================
//
//�V���b�N�u���[�R���g���[���w�b�_[ShockBlurController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SHOCKBLURCONTROLLER_H_
#define _SHOCKBLURCONTROLLER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"
#include "BaseEffectController.h"
#include "Effect/ShockBlur.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class ShockBlurController : public BaseSingleton<ShockBlurController>, public BaseEffectController
{
public:
	friend class BaseSingleton<ShockBlurController>;

	void Update();
	void Draw(LPDIRECT3DTEXTURE9 targetTexture);
	void SetBlur(D3DXVECTOR3 pos, float power, int duration);

private:
	enum State
	{
		Start,
		Wait,
		End,
		Max
	};

	ShockBlurController();
	~ShockBlurController();

	ShockBlur *shockBlur;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DSURFACE9 surface;

	bool active;
	bool drawFlag;

	float srcPower, destPower;
	int cntFrame;
	int state;
	int effectTime;

	void OnStart();
	void OnWait();
	void OnEnd();
};

#endif