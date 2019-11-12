//=====================================
//
//PlaceConfig.h
//�@�\:�v���C�X�ݒ�
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLACECONFIG_H_
#define _PLACECONFIG_H_

#include <vector>
#include <algorithm>
#include <memory>
#include "../../Framework/Math/TMath.h"

/**************************************
�}�N����`
***************************************/
#define DEBUG_PLACEMODEL

namespace Field::Model
{
	/**************************************
	�O���錾
	***************************************/
	class RouteModel;
	class PlaceModel;

	/**************************************
	using�錾
	***************************************/
	using RouteModelPtr = std::shared_ptr<RouteModel>;
	using RouteContainer = std::vector<std::shared_ptr<RouteModel>>;

	/**************************************
	PlaceModel�̃^�C�v��\���񋓎q
	***************************************/
	enum PlaceType
	{
		None,			//�������
		Road,			//��
		Town,			//�X
		River,			//��
		Bridge,			//��
		Junction,		//�����_
		Mountain		//�R
	};
}

#endif