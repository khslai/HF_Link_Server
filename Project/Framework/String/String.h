//=====================================
//
//String.h
//�@�\:�����񑀍�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STRING_H_
#define _STRING_H_

#include "../../main.h"
#include <vector>

namespace String
{
	/**************************************
	�����񕪊��֐�
	***************************************/
	void Split(std::vector<std::string>& out, std::string& str, const char delim);

}

#endif