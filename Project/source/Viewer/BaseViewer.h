//=============================================================================
//
// 基底ビューアヘッダ[BaseViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BaseViewer_H_
#define _BaseViewer_H_

#include "Framework/PolygonDrawer.h"
#include <string>
#include <vector>

class PolygonDrawer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class BaseViewer
{
protected:
	bool Active = false;
	bool InIdle = true;

public:
	BaseViewer() {};
	virtual ~BaseViewer() {};

	virtual void Start() = 0;
	virtual bool Update() = 0;
	virtual void Draw() = 0;
	virtual void Exit() = 0;
	virtual void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) = 0;
	virtual void CreateViewerTex(LPDIRECT3DTEXTURE9* TexturePtr) {};
};

#endif