//=====================================
//
//�X�s�[�h�u���[�R���g���[���w�b�_[SpeedBlurController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPEEDBLURCONROLLER_H_
#define _SPEEDBLURCONROLLER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"
#include "BaseEffectController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�O���錾
***************************************/
class SpeedBlur;

/**************************************
�N���X��`
***************************************/
class SpeedBlurController : public BaseSingleton<SpeedBlurController>, public BaseEffectController
{
public:
	friend class BaseSingleton<SpeedBlurController>;

	void Update();
	void Draw(LPDIRECT3DTEXTURE9 targetTexture = NULL);
	void SetPower(float power);
	void AddPower(float power);

private:
	SpeedBlurController();
	~SpeedBlurController();

	SpeedBlur *speedBlur;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DSURFACE9 surface;

	float startPower, endPower;
	int cntPower;
};

#endif