//=====================================
//
// PlayerPrefs.h
// �@�\:�f�[�^�ۑ��@�\
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERPREFS_H_
#define _PLAYERPREFS_H_

#include <string>
#include <unordered_map>
#include <fstream>

#include "../../Library/nameof/nameof.hpp"
#include "../../Library/picojson/picojson.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class PlayerPrefs
{
public:

	/*********************************************
	�ۑ������f�[�^�̎擾����
	*********************************************/
	//bool�^
	static bool GetBool(const std::string& key);

	//string�^
	static std::string GetString(const std::string& key);

	//���l�^
	template<class T>
	static T GetNumber(const std::string& key)
	{
		picojson::value value = GetData(key);

		if (value.is<picojson::null>())
			return 0;

		return static_cast<T>(value.get<double>());
	}

	/*********************************************
	�f�[�^�̕ۑ�����
	*********************************************/
	//bool�^
	static void SaveBool(const std::string& key, bool value);

	//string�^
	static void SaveString(const std::string& key, const std::string& value);

	//int�^
	template<class T>
	static void SaveNumber(const std::string& key, T value)
	{
		Save<double>(key, static_cast<double>(value));
	}

private:
	PlayerPrefs();
	
	//����������
	template<class T>
	static void Initialize(const std::string& key, T value)
	{
		picojson::object data;
		data.emplace(key, picojson::value(value));

		std::string serializeData = picojson::value(data).serialize();
		std::ofstream ofs;
		ofs.open(FileName, std::ios::out);
		ofs << serializeData << std::endl;
		ofs.close();
	}

	//�ۑ�����
	template <class T>
	static void Save(const std::string& key, T value)
	{
		std::ifstream ifs;
		ifs.open(FileName, std::ios::binary);

		if (ifs.is_open())
		{
			picojson::value val;
			ifs >> val;
			ifs.close();

			picojson::object obj = val.get<picojson::object>();
			val.get<picojson::object>()[key] = picojson::value(value);

			std::string serializeData = val.serialize();
			std::ofstream ofs;
			ofs.open(FileName, std::ios::out);
			ofs << serializeData << std::endl;
			ofs.close();
		}
		else
		{
			Initialize<T>(key, value);
		}
	}

	//JSON�擾����
	static picojson::value GetData(const std::string& key);

	static const char* FileName;
};

#endif