//=====================================
//
//SerialWrapper.cpp
//�@�\:�V���A���ʐM�@�\���b�p�[�N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SerialWrapper.h"

#include <tchar.h>

/**************************************
�R���X�g���N�^
***************************************/
SerialWrapper::SerialWrapper(int comNum)
{
	TCHAR com[10];
	_stprintf_s(com, 10, _T("COM%d"), comNum);

	//�V���A���|�[�g���J��
	comPort = CreateFile(com, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	assert(comPort != INVALID_HANDLE_VALUE);
}

/**************************************
�f�X�g���N�^
***************************************/
SerialWrapper::~SerialWrapper()
{
	//�V���A���|�[�g�����
	CloseHandle(comPort);
}

/**************************************
�ʐM�J�n����
***************************************/
void SerialWrapper::Begin(unsigned long speed)
{
	DCB dcb;		//�V���A���|�[�g�̍\����񂪓���\����
	GetCommState(comPort, &dcb);

	dcb.BaudRate = speed;					//���x
	dcb.ByteSize = 8;						//�f�[�^��
	dcb.Parity = NOPARITY;					//�p���e�B
	dcb.StopBits = ONESTOPBIT;				//�X�g�b�v�r�b�g��
	dcb.fOutxCtsFlow = FALSE;				//���M��CTS�t���[
	dcb.fRtsControl = RTS_CONTROL_ENABLE;	//RTS�t���[

	//�ύX�����ݒ�l����������
	SetCommState(comPort, &dcb);
}

/**************************************
���M����
***************************************/
size_t SerialWrapper::Write(char data)
{
	char* sentData = &data;		//���M����1Byte
	DWORD numberOfPut;			//���ۂɑ��M����Byte��

	//�|�[�g�֑��M
	WriteFile(comPort, sentData, 1, &numberOfPut, NULL);

	return numberOfPut;
}

/**************************************
���M����
***************************************/
size_t SerialWrapper::Write(const char buf[], int length)
{
	DWORD lengthOfSent = length;		//���M����Byte��
	DWORD numberOfPut;					//���ۂɑ��M����Byte��

	//�|�[�g�֑��M
	WriteFile(comPort, buf, lengthOfSent, &numberOfPut, NULL);

	return numberOfPut;
}

/**************************************
��M�o�b�t�@�ɗ��܂���Byte��
***************************************/
int SerialWrapper::Available()
{
	//��M�f�[�^���𒲂ׂ�
	DWORD errors;
	COMSTAT comStat;
	ClearCommError(comPort, &errors, &comStat);

	int lengthOfReceived = comStat.cbInQue;		//��M�������b�Z�[�W�����擾

	return lengthOfReceived;
}

/**************************************
�ǂݍ��ݏ���
***************************************/
int SerialWrapper::Read()
{
	if (Available() < 1)
		return -1;

	char buf[1];			//��M�f�[�^�i�[�p
	DWORD numberOfRead;		//���ۂɎ�M�����o�C�g��

	//�f�[�^��M
	bool result = ReadFile(comPort, buf, 1, &numberOfRead, NULL);

	if (result == FALSE)
	{
		return -1;
	}
	else
	{
		return buf[0];
	}
}
