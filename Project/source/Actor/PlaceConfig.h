//=====================================
//
//PlaceConfig.h
//@\:vCXέθ
//Author:GP12B332 21 §ΤYΎ
//
//=====================================
#ifndef _PLACECONFIG_H_
#define _PLACECONFIG_H_

#include <vector>
#include <algorithm>
#include <memory>
#include "../../Framework/Math/TMath.h"

/**************************************
}Nθ`
***************************************/
#define DEBUG_PLACEMODEL

namespace Field::Model
{
	/**************************************
	OϋιΎ
	***************************************/
	class RouteModel;
	class PlaceModel;

	/**************************************
	usingιΎ
	***************************************/
	using RouteModelPtr = std::shared_ptr<RouteModel>;
	using RouteContainer = std::vector<std::shared_ptr<RouteModel>>;

	/**************************************
	PlaceModelΜ^Cvπ\·ρq
	***************************************/
	enum PlaceType
	{
		None,			//ϊσΤ
		Road,			//Ή
		Town,			//X
		River,			//μ
		Bridge,			//΄
		Junction,		//π·_
		Mountain		//R
	};
}

#endif