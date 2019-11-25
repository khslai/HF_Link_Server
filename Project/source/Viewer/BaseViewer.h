//=============================================================================
//
// ���r���[�A�w�b�_[BaseViewer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _BaseViewer_H_
#define _BaseViewer_H_

#include <string>
#include <vector>

class BaseViewer
{
public:
	BaseViewer() {};
	~BaseViewer() {};

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) = 0;
};

#endif