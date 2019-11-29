//=============================================================================
//
// 基底ビューアヘッダ[BaseViewer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _BaseViewer_H_
#define _BaseViewer_H_

#include <string>
#include <vector>
#include <functional>

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

	virtual bool Update() = 0;
	virtual void Draw() = 0;
	virtual void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) = 0;
	//virtual void CreateViewerTex(LPDIRECT3DTEXTURE9* TexturePtr) {};
	//virtual void RankingRecovery(void) {};
	//virtual string GetLastScore(void) {};
};

#endif