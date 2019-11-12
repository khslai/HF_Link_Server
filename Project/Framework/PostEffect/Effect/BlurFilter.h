//=====================================
//
//�u���[�t�B���^�[�w�b�_[BlurFilter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BLURFILTER_H_
#define _BLURFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"
#include <vector>

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BlurFilter : public ScreenObject {
public:
	BlurFilter(DWORD width, DWORD height);
	~BlurFilter();
	void DrawEffect(UINT pass);							//�`�揈��

private:
	static const int SizeTexelArray;

	LPD3DXEFFECT effect;								//�V�F�[�_
	D3DXHANDLE texelU, texelV;							//�e�n���h��

	std::vector<float> offsetTexelU;
	std::vector<float> offsetTexelV;
};

#endif