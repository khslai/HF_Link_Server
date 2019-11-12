//=====================================
//
//�X�p�C�N�m�C�Y�R���g���[���w�b�_[SpikeNoiseController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SPIKENOISECONTROLLER_H_
#define _SPIKENOISECONTROLLER_H_

#include "../../main.h"
#include "../Pattern/BaseSingleton.h"
#include "BaseEffectController.h"
/**************************************
�O���錾
***************************************/
class SpikeNoise;

/**************************************
�N���X��`
***************************************/
class SpikeNoiseController : public BaseSingleton<SpikeNoiseController>, public BaseEffectController
{
public:
	friend class BaseSingleton<SpikeNoiseController>;

	void SetNoise(float power, int duration);
	void Update();
	void Draw(LPDIRECT3DTEXTURE9 targetTexture = NULL);

private:
	enum State
	{
		Start,
		Wait,
		End,
		Max
	};

	SpikeNoiseController();
	~SpikeNoiseController();

	SpikeNoise *spikeNoise;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DSURFACE9 surface;

	bool drawFlag;

	bool active;
	int cntFrame;
	int effectTime;
	int state;
	float destPower, srcPower;
	float base;

	void OnStart();
	void OnWait();
	void OnEnd();
};

#endif