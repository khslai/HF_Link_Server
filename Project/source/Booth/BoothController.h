//=====================================
//
//BoothController.h
//�@�\:�u�[�X�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOOTHCONTROLLER_H_
#define _BOOTHCONTROLLER_H_

#include "../../main.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�O���錾
***************************************/
class SerialWrapper;

enum BlinkType
{
	InsertRank,
	PlusEventLED,
	MinusEventLED,
	GradeUp,
};

/**************************************
�N���X��`
***************************************/
class BoothController : public BaseSingleton<BoothController>
{
public:
	void Init();
	void Uninit();

	void RotateTable(unsigned char angle);

	void BlinkLED(BlinkType Type);

private:
	SerialWrapper * serial;

	BoothController() {};
	BoothController(const BoothController&) {};
	friend class BaseSingleton<BoothController>;
};
#endif