//=====================================
//
// �V�e�B�A�N�^�[[CityActor.cpp]
// �@�\�F�s�s�i���A���j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _CITYACTOR_H_
#define _CITYACTOR_H_

#include "PlaceActor.h"

//**************************************
// �N���X��`
//**************************************
class CityActor : public PlaceActor
{
public:
	CityActor(const D3DXVECTOR3& pos);
	~CityActor();
};

#endif
