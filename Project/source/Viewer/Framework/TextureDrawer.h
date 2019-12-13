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

enum ExpandType
{
	LeftToRight,
	RightToLeft,
	ExpandUpToDown,
	ExpandDownToUp,
	ToUpDown,
	ToLeftRight,
};

enum CloseType
{
	FromUpDown,
	FromLeftRight,
	CloseUpToDown,
	CloseDownToUp,
};


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class TextureDrawer : public BaseTextureDrawer
{
private:
	int CountFrame = 0;
	float Duration;			// �Ԋu
	float DestScale;		// �g��A�k�����̖ڕW�X�P�[��
	float StartAlpha;		// �t�F�C�h���̍ŏ��A���t�@
	float DestAlpha;		// �t�F�C�h���̖ڕW�A���t�@
	D3DXVECTOR3 StartPos;	// �ړ����̎n�_
	D3DXVECTOR3 DestPos;	// �ړ����̏I�_
	D3DXVECTOR2 StartSize;	// �g��A�k�����̍ŏ��X�P�[��
	D3DXVECTOR2 Devide;		// �e�N�X�`���̕�����
	D3DXVECTOR2 UnitUV;		// �P�ʃe�N�X�`����UV���W
	D3DXVECTOR2 Index;		// �\������e�N�X�`���̃C���f�b�N�X
	EaseType easeType;
	ExpandType expandType;
	CloseType closeType;
	bool InMove = false;
	bool InScale = false;
	bool InExpand = false;
	bool InClose = false;
	bool InFade = false;
	std::function<void(void)> Callback;

	void MakeVertex(void);
	void SetVertex(void);
	void SetTexture(void);
	void Expand_LeftToRight(float Time);
	void Expand_RightToLeft(float Time);
	void Expand_UpToDown(float Time);
	void Expand_DownToUp(float Time);
	void Expand_ToUpDown(float Time);
	void Expand_ToLeftRight(float Time);
	void Close_FromUpDown(float Time);
	void Close_FromLeftRight(float Time);
	void Close_UpToDown(float Time);
	void Close_DownToUp(float Time);
public:
	// �����Ȃ��e�N�X�`���p
	TextureDrawer(D3DXVECTOR2 TextureSize, bool Visible = true);		
	// ��������e�N�X�`���p
	TextureDrawer(D3DXVECTOR2 TextureSize, int DevideX, int DevideY, bool Visible = true);
	~TextureDrawer();

	void Update();
	void SetPosition(D3DXVECTOR3 Pos);
	void SetIndex(int Index);
	void SetIndex(int x,int y);
	void SetScale(float Scale);
	void SetScale(float Duration, float Scale, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Expand(float Duration, ExpandType expandType, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Close(float Duration, CloseType closeType, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Move(float Duration, D3DXVECTOR3 DestPos, EaseType Type = EaseType::Linear, std::function<void(void)> callback = nullptr);
	void Fade(float Duration, float DestAlpha, std::function<void(void)> callback = nullptr);
};

#endif