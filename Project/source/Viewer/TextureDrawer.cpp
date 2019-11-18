//=============================================================================
//
// テクスチャ描画クラス [TextureDrawer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include"../../main.h"
#include "TextureDrawer.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Math/Easing.h"

//=============================================================================
// コンストラクタ
//=============================================================================
TextureDrawer::TextureDrawer(D3DXVECTOR2 TextureSize) :
	DevideX(1),
	DevideY(1),
	TextureSize(TextureSize),
	UnitUV(D3DXVECTOR2(1.0f,1.0f))
{
	MakeVertex();
}

//=============================================================================
// コンストラクタ
//=============================================================================
TextureDrawer::TextureDrawer(int DevideX, int DevideY, D3DXVECTOR2 TextureSize) :
	DevideX(DevideX),
	DevideY(DevideY)
{
	UnitUV.x = 1.0f / DevideX;
	UnitUV.y = 1.0f / DevideY;
	this->TextureSize.x = TextureSize.x / DevideX;
	this->TextureSize.y = TextureSize.y / DevideY;
	MakeVertex();
}

//=============================================================================
// デストラクタ
//=============================================================================
TextureDrawer::~TextureDrawer()
{
	SAFE_RELEASE(Texture);
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void TextureDrawer::LoadTexture(const char *path)
{
	ResourceManager::Instance()->GetTexture(path, Texture);
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
void TextureDrawer::LoadTexture(LPDIRECT3DTEXTURE9 *Texture)
{
	if (this->Texture != nullptr)
	{
		SAFE_RELEASE(this->Texture);
	}
	this->Texture = *Texture;
}

//=============================================================================
// オブジェクト描画処理
//=============================================================================
void TextureDrawer::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, Texture);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, Vertex, sizeof(VERTEX_2D));
}


//=============================================================================
// 頂点の作成
//=============================================================================
void TextureDrawer::MakeVertex()
{
	// 頂点座標の設定
	SetVertex();

	// テクスチャのパースペクティブコレクト用
	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;

	// テクスチャ色の設定
	SetColor(SET_COLOR_NOT_COLORED);

	// テクスチャ座標の設定
	SetTexture(0);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void TextureDrawer::SetVertex(void)
{
	// 頂点座標の設定
	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2, TextureSize.y / 2, 0.0f);
}

//=============================================================================
// テクスチャUV設定処理
//=============================================================================
void TextureDrawer::SetTexture(void)
{
	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=============================================================================
// テクスチャUV設定処理
//=============================================================================
void TextureDrawer::SetTexture(int UnitNo)
{
	int x = UnitNo % DevideX;
	int y = UnitNo / DevideX;

	Vertex[0].tex = D3DXVECTOR2(x * UnitUV.x, y * UnitUV.y);
	Vertex[1].tex = D3DXVECTOR2((x + 1) * UnitUV.x, y * UnitUV.y);
	Vertex[2].tex = D3DXVECTOR2(x * UnitUV.x, (y + 1) * UnitUV.y);
	Vertex[3].tex = D3DXVECTOR2((x + 1) * UnitUV.x, (y + 1) * UnitUV.y);
}

//=============================================================================
// テクスチャ展開演出処理
//=============================================================================
void TextureDrawer::SetTextureExpand(float Time)
{
	float VtxPercent = Easing::EaseValue(Time, -1.0f, 1.0f, EaseType::InQuart);
	float TexPercent = Easing::EaseValue(Time, 0.0f, 1.0f, EaseType::InQuart);

	// 頂点座標の設定
	Vertex[0].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, -TextureSize.y / 2, 0.0f);
	Vertex[1].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, -TextureSize.y / 2, 0.0f);
	Vertex[2].vtx = Position + D3DXVECTOR3(-TextureSize.x / 2, TextureSize.y / 2, 0.0f);
	Vertex[3].vtx = Position + D3DXVECTOR3(TextureSize.x / 2 * VtxPercent, TextureSize.y / 2, 0.0f);

	Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	Vertex[1].tex = D3DXVECTOR2(TexPercent, 0.0f);
	Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	Vertex[3].tex = D3DXVECTOR2(TexPercent, 1.0f);
}

//=============================================================================
// テクスチャのアルファ値設定処理（透過）
//=============================================================================
void TextureDrawer::SetAlpha(float alpha)
{
	D3DXCOLOR Color = Vertex[0].diffuse;
	Color.a = alpha;

	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//=============================================================================
// テクスチャの色設定処理
//=============================================================================
void TextureDrawer::SetColor(D3DXCOLOR Color)
{
	Vertex[0].diffuse = Color;
	Vertex[1].diffuse = Color;
	Vertex[2].diffuse = Color;
	Vertex[3].diffuse = Color;
}

//=============================================================================
// 描画座標設定処理
//=============================================================================
void TextureDrawer::SetPosition(D3DXVECTOR3 Pos)
{
	this->Position = Pos;
	SetVertex();
}
