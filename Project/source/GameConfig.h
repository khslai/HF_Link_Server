//=====================================
//
//GameConfig.h
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMECONFIG_H_
#define _GAMECONFIG_H_

namespace GameConfig
{
	/**************************************
	シーンのID
	***************************************/
	enum SceneID
	{
		Game,
		TextureTest,
		Max
	};

	/**************************************
	データ保存用のキー
	***************************************/
	enum SaveKey
	{
		Key_RemainTime,		//制限時間
		Key_ItemStock,		//アイテムストック
		Key_FieldLevel		//フィールドレベル
	};
}

#endif