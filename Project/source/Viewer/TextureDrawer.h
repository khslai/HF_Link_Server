//=============================================================================
//
// テクスチャ描画クラス [TextureDrawer.h]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#ifndef _TextureDrawer_H_
#define _TextureDrawer_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 色定義
#define SET_COLOR_NOT_COLORED	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_BLACK			(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_RED			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_GREEN			(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_BLUE			(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_YELLOW		(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_PINK			(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_RIGHTBLUE		(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_ORANGE		(D3DXCOLOR(1.0f,0.4f,0.0f,1.0f))

enum TexExpandType
{
	LeftToRight,
	Expand_UpDown,
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class TextureDrawer
{
private:
	int DevideX;
	int DevideY;
	D3DXVECTOR3	Position;
	D3DXVECTOR2	TextureSize;
	D3DXVECTOR2 UnitUV;
	VERTEX_2D Vertex[NUM_VERTEX];
	LPDIRECT3DTEXTURE9 Texture = nullptr;

	void MakeVertex();
	void SetVertex();
	void SetTexture(void);
public:
	TextureDrawer(D3DXVECTOR2 TextureSize);
	TextureDrawer(int DevideX, int DevideY, D3DXVECTOR2 TextureSize);
	virtual ~TextureDrawer();

	void Draw();
	void LoadTexture(const char *path);
	void LoadTexture(LPDIRECT3DTEXTURE9* Texture);
	void SetAlpha(float alpha);
	void SetColor(D3DXCOLOR color);
	void SetPosition(D3DXVECTOR3 Pos);
	void SetTexture(int Index);
	void TexExpand_LeftToRight(float Time);
	void TexExpand_ToUpDown(float Time);
	void TexExpand_ToUpDown(float Time, int Index);


};

#endif