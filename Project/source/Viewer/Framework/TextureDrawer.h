//=============================================================================
//
// �e�N�X�`���`��N���X [TextureDrawer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _TextureDrawer_H_
#define _TextureDrawer_H_

#include <functional>
#include "BaseTextureDrawer.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TextureDrawer : public BaseTextureDrawer
{
private:
	float Duration;
	float DestScale;
	D3DXVECTOR3 StartPos;
	D3DXVECTOR3 DestPos;
	D3DXVECTOR2 StartSize;
	std::function<void(void)> Callback;

	void MakeVertex();
	void SetVertex();
	void SetTexture(void);
	void Expand_LeftToRight(float Time);
	void Expand_RightToLeft(float Time);
	void Expand_ToUpDown(float Time);
	void Close_UpDown(float Time);
	void Close_LeftRight(float Time);
public:
	TextureDrawer(D3DXVECTOR2 TextureSize, bool Visible = true);
	~TextureDrawer();

	void Update();
	void SetPosition(D3DXVECTOR3 Pos);
	void SetScale(float Scale);
	void SetScale(float Duration, float Scale, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Expand(float Duration, int expandType, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Close(float Duration, int closeType, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Move(float Duration, D3DXVECTOR3 DestPos, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
};

#endif