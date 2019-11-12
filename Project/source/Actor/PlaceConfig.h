//=====================================
//
//PlaceConfig.h
//機能:プレイス設定
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLACECONFIG_H_
#define _PLACECONFIG_H_

#include <vector>
#include <algorithm>
#include <memory>
#include "../../Framework/Math/TMath.h"

/**************************************
マクロ定義
***************************************/
#define DEBUG_PLACEMODEL

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class RouteModel;
	class PlaceModel;

	/**************************************
	using宣言
	***************************************/
	using RouteModelPtr = std::shared_ptr<RouteModel>;
	using RouteContainer = std::vector<std::shared_ptr<RouteModel>>;

	/**************************************
	PlaceModelのタイプを表す列挙子
	***************************************/
	enum PlaceType
	{
		None,			//初期状態
		Road,			//道
		Town,			//街
		River,			//川
		Bridge,			//橋
		Junction,		//交差点
		Mountain		//山
	};
}

#endif