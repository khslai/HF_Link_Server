//=====================================
//
//�X�s�[�h�u���[�t�B���^�[�w�b�_[SpeedBlurFilter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPEEDBLURFILTER_H_
#define _SPEEDBLURFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SpeedBlur : public ScreenObject
{
public:
	SpeedBlur(DWORD width, DWORD height);
	~SpeedBlur();
	void DrawEffect();
	void SetPower(float power);
	void SetCenterPos(const D3DXVECTOR3& pos);
	void SetStartLength(float length);
	void SetAspectRatio(float width, float height);

private:
	LPD3DXEFFECT effect;
	D3DXHANDLE hPower, hCenter;
	D3DXHANDLE hTU, hTV;
	D3DXHANDLE hStartLength;
	D3DXHANDLE hAspectRatio;

	float texelU, texelV;
};

#endif