//=====================================
//
//���m�g�[���t�B���^�w�b�_[MonotoneFilter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MONOTONEFILTER_H_
#define _MONOTONEFILTER_H_

#include "../../../main.h"
#include "../ScreenObject.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class MonotoneFilter : ScreenObject {
public:
	MonotoneFilter(DWORD width, DWORD height);
	~MonotoneFilter();

	void Draw();									//�`�揈��
	void SetPower(float power);						//�����ݒ菈��

private:
	LPD3DXEFFECT effect;							//�V�F�[�_
	D3DXHANDLE hndlPower;							//�e�n���h��
};

#endif