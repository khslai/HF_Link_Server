//=============================================================================
//
// �e�N�X�`���`��(��������)�N���X [SplitTextureDrawer.h]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#ifndef _SplitTextureDrawer_H_
#define _SplitTextureDrawer_H_

#include "BaseTextureDrawer.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SplitTextureDrawer : public BaseTextureDrawer
{
private:
	int DevideX;
	int DevideY;
	int IndexX;
	int IndexY;
	D3DXVECTOR2 UnitUV;

	void MakeVertex();
	void SetVertex();
	void SetTexture();
public:
	SplitTextureDrawer(int DevideX, int DevideY, D3DXVECTOR2 TextureSize, bool Visible = true);
	virtual ~SplitTextureDrawer();

	void Update();
	void SetPosition(D3DXVECTOR3 Pos);
	void SetIndex(int Index);
	void Expand_LeftToRight(float Time, EaseType Type);
	void Expand_RightToLeft(float Time, EaseType Type);
	void Expand_ToUpDown(float Time, EaseType Type);
	void Close_UpDown(float Time, EaseType Type);
	void Close_LeftRight(float Time, EaseType Type);
};

#endif