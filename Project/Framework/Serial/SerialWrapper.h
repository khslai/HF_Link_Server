//=====================================
//
//SerialWrapper.h
//�@�\:�V���A���ʐM�@�\�̃��b�p�[�N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SERIALWRAPPER_H_
#define _SERIALWRAPPER_H_

#include "../../main.h"

/**************************************
�N���X��`
***************************************/
class SerialWrapper
{
public:
	//�R���X�g���N�^
	//comNum : �J��COM�|�[�g�̔ԍ�
	SerialWrapper(int comNum);

	//�f�X�g���N�^
	~SerialWrapper();

	//�V���A���ʐM�̏�����
	//spped : �`�����x
	void Begin(unsigned long speed);

	//1Byte�̃f�[�^�𑗐M����
	//char data : ���M����1Byte�f�[�^
	virtual size_t Write(char data);

	//����Byte�̃f�[�^�𑗐M����
	//const char buf[] : ���M�f�[�^��
	//int length : ���M�f�[�^��
	virtual size_t Write(const char buf[], int length);

	//��M�o�b�t�@�ɗ��܂���Byte����Ԃ�
	virtual int Available();

	//��M�o�b�t�@����1Byte�ǂݍ���
	virtual int Read();

private:
	HANDLE comPort;

	bool initialized;
};

#endif