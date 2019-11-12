//=====================================
//
//Template.cpp
//�@�\:�����񑀍�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "String.h"

/**************************************
�����񕪊�����
***************************************/
void String::Split(std::vector<std::string>& out, std::string & str, const char delim)
{
	unsigned first = 0;							//�n�_
	unsigned last = str.find_first_of(delim);	//�I�_

	while (first < str.size())
	{
		//�J���}�̈ʒu�܂ł̕������؂�o��
		std::string subStr(str, first, last - first);

		out.push_back(subStr);

		//���ɃJ���}�������Ƃ��܂Ŏn�_�ƏI�_���X�V
		first = last + 1;
		last = str.find_first_of(delim, first);

		if (last == std::string::npos)
		{
			last = str.size();
		}

	}
}
