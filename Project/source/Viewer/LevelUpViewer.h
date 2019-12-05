//=============================================================================
//
// ���x���A�b�v���p�N���X [LevelUpViewer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _LevelUpViewer_H_
#define _LevelUpViewer_H_

#include <string>
#include <vector>
#include <functional>
#include "BaseViewer.h"

class TextureDrawer;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class LevelUpViewer : public BaseViewer
{
private:
	int State;								// ���
	int CountFrame;

	TextureDrawer* Celebration;
	std::vector<TextureDrawer*> Text;

public:
	std::function<void(void)> Recovery;

	LevelUpViewer(std::function<void(void)> recovery);
	~LevelUpViewer();
	void Update(void) override;
	void Draw(void) override;
	void ReceivePacket(int PacketType, const std::vector<std::string>& SpliteStr) override;
};

#endif
