//=====================================
//
//BoothController.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BoothController.h"
#include "../../Framework/Serial/SerialWrapper.h"
#include "../../Framework/Core/PlayerPrefs.h"

/**************************************
����������
***************************************/
void BoothController::Init()
{
	int comNum = PlayerPrefs::GetNumber<int>("ComPort");

	serial = new SerialWrapper(comNum);
	serial->Begin(9600);
}

/**************************************
�擾����
***************************************/
void BoothController::Uninit()
{
	SAFE_DELETE(serial);
}

/**************************************
��]����
***************************************/
void BoothController::RotateTable(unsigned char angle)
{
	size_t numPut = serial->Write(angle);
}

/**************************************
LED�_�ŏ���
***************************************/
void BoothController::BlinkLED(BlinkType Type)
{
	if (Type == BlinkType::InsertRank)
		serial->Write('r');
	else if (Type == BlinkType::PlusEventLED)
		serial->Write('p');
	else if (Type == BlinkType::MinusEventLED)
		serial->Write('m');
	else if (Type == BlinkType::GradeUp)
		serial->Write('g');
}
