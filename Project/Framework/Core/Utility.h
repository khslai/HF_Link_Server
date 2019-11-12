//=====================================
//
//���[�e�B���e�B�w�b�_[Utility.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <algorithm>
#include "../../Library/nameof/nameof.hpp"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
namespace Utility
{
	/**************************************
	�N���X��`
	***************************************/
	template <class T>
	static void DeleteContainer(T& container)
	{
		for (auto&& p : container)
		{
			delete p;
			p = NULL;
		}
		container.clear();
	}

	/**************************************
	�N���X��`
	***************************************/
	template <class T>
	static void DeleteMap(T& map)
	{
		for (auto&& pair : map)
		{
			delete pair.second;
			pair.second = NULL;
		}
		map.clear();
	}

	/**************************************
	�R���e�i����������
	***************************************/
	template<class T, class OBJ>
	static inline bool IsContain(T& container, const OBJ& target)
	{
		auto itr = std::find(container.begin(), container.end(), target);

		return itr != container.end();
	}

	/**************************************
	enum�̕�����
	***************************************/
	template <class Enum>
	std::string ToString(const Enum& val)
	{
		return std::string(NAMEOF_ENUM(val));
	}
};

#endif