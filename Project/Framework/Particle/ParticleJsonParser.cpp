//=====================================
//
//�p�[�e�B�N��JSON�p�[�T����[ParticleJsonParser.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ParticleJsonParser.h"
#include "../../Library/json11/json11.hpp"
#include <fstream>

using namespace std;
/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ParticleJsonParser::ParticleJsonParser(const char * fileName)
{
	//JSON�t�@�C�����J��
	string filePath = "data/PARTICLE/" + string(fileName) + ".json";
	ifstream ifs;
	ifs.open(filePath, std::ios::in);

	//�����m�F
	assert(ifs.is_open());

	//JSON�f�[�^��ǂݍ���
	const string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	string err;
	json11::Json data = json11::Json::parse(json, err);

	assert(err.empty());

	//JSON�f�[�^���p�[�X
	texturePath = data["texturePath"].string_value();
	particleMax = data["particleMax"].int_value();
	emitterMax = data["emitterMax"].int_value();
	emitNumMin = data["emitNumMin"].int_value();
	emitNumMax = data["emitNumMax"].int_value();
	durationMin = data["durationMin"].int_value();
	durationMax = data["durationMax"].int_value();
	size.x = (float)data["sizeX"].number_value();
	size.y = (float)data["sizeY"].number_value();
	texDiv.x = (float)data["divX"].number_value();
	texDiv.y = (float)data["divY"].number_value();
}

/**************************************
�e�N�X�`���p�X�擾
***************************************/
std::string ParticleJsonParser::GetTexturePath() const
{
	return texturePath;
}

/**************************************
�p�[�e�B�N���ő吔�擾
***************************************/
int ParticleJsonParser::GetParticleMax() const
{
	return particleMax;
}

/**************************************
�G�~�b�^�ő吔�擾
***************************************/
int ParticleJsonParser::GetEmitterMax() const
{
	return emitterMax;
}

/**************************************
���o���擾
***************************************/
int ParticleJsonParser::GetEmitNum() const
{
	if (emitNumMin != 0 && emitNumMax != 0)
		return Math::RandomRange(emitNumMin, emitNumMax);
	
	if (emitNumMax != 0)
		return emitNumMax;

	return emitNumMin;
}

/**************************************
���o���Ԏ擾
***************************************/
int ParticleJsonParser::GetDuration() const
{
	if (durationMin != 0 && durationMax != 0)
		return Math::RandomRange(durationMin, durationMax);

	if (durationMax != 0)
		return durationMax;

	return durationMin;
}

/**************************************
�T�C�Y�擾
***************************************/
D3DXVECTOR2 ParticleJsonParser::GetSize() const
{
	return size;
}

/**************************************
UV�����擾
***************************************/
D3DXVECTOR2 ParticleJsonParser::GetTexDiv() const
{
	return texDiv;
}
