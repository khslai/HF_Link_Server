//=====================================
//
//�f�[�^�ۑ��@�\����[PlayerPrefs.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PlayerPrefs.h"


/**************************************
�O���[�o���ϐ�
***************************************/
const char* PlayerPrefs::FileName = "data/data.bin";

/**************************************
bool�擾����
***************************************/
bool PlayerPrefs::GetBool(const std::string & key)
{
	picojson::value value = GetData(key);

	if (!value.is<picojson::null>())
		return false;

	return value.get<bool>();
}

/**************************************
String�擾����
***************************************/
std::string PlayerPrefs::GetString(const std::string & key)
{
	picojson::value value = GetData(key);

	if (!value.is<picojson::null>())
		return false;

	return value.get<std::string>();
}

/**************************************
bool�ۑ�����
***************************************/
void PlayerPrefs::SaveBool(const std::string & key, bool value)
{
	Save<bool>(key, value);
}

/**************************************
String�ۑ�����
***************************************/
void PlayerPrefs::SaveString(const std::string & key, const std::string & value)
{
	Save<const std::string&>(key, value);
}

/**************************************
JSON�擾����
***************************************/
picojson::value PlayerPrefs::GetData(const std::string & key)
{
	std::ifstream ifs;
	ifs.open(FileName, std::ios::binary);

	picojson::value val;
	ifs >> val;
	ifs.close();

	picojson::object object = val.get<picojson::object>();

	if (object.count(key) == 0)
		return picojson::value();
	
	return object[key];
}