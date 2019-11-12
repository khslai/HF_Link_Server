//=====================================
//
//メッシュコンテナ処理[MeshContainer.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "MeshContainer.h"
#include "../Resource/MeshResource.h"

/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
MeshContainer::MeshContainer() :
	mesh(NULL),
	materialNum(0),
	resource(NULL),
	initialized(false)
{

}

/**************************************
デストラクタ
***************************************/
MeshContainer::~MeshContainer()
{
	ReleaseResource();
}

/**************************************
描画処理
***************************************/
void MeshContainer::Draw()
{
	D3DMATERIAL9 matDef;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//マテリアル退避
	pDevice->GetMaterial(&matDef);

	for (DWORD i = 0; i < materialNum; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, textures[i]);

		//マテリアル設定
		pDevice->SetMaterial(&materials[i]);

		//描画
		mesh->DrawSubset(i);
	}

	//マテリアル復元
	pDevice->SetMaterial(&matDef);
}

/**************************************
モデルのワイヤーフレームを描画
***************************************/
void MeshContainer::DrawWireframe(bool InDesingMode)
{
	D3DMATERIAL9 matDef;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ワイヤーフレーム描画フラグ
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//マテリアル退避
	pDevice->GetMaterial(&matDef);

	//DrawSurfaceNum += 100;
	//DrawSurfaceNum %= TotalSurfaceNum;

	// 頂点フォーマットの設定
	//pDevice->SetFVF(MeshFVF);

	//pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_3D));
	//pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | 1);

	//pDevice->SetIndices(IndexBuffer);

	//pDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(VERTEX_BILLBOARD));
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh->GetNumVertices(), 0, mesh->GetNumFaces());
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, TotalSurfaceNum, VertexBuffer, sizeof(VERTEX_2D));

	//for (DWORD i = 0; i < TotalSurfaceNum; i++)
	//{
	//	//pDevice->SetTexture(0, textureContainer[i]);
	//	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX * i, NUM_POLYGON);
	//}
	
#if 1
	for (DWORD i = 0; i < materialNum; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, textures[i]);

		//マテリアル設定
		pDevice->SetMaterial(&materials[i]);

		//描画
		mesh->DrawSubset(i);
	}
#endif

	//マテリアル復元
	pDevice->SetMaterial(&matDef);

	// ワイヤーフレーム終了処理
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}


/**************************************
マテリアル数取得処理
***************************************/
UINT MeshContainer::GetMaterialNum()
{
	return materialNum;
}

/**************************************
マテリアル取得処理
***************************************/
void MeshContainer::GetMaterial(UINT index, D3DMATERIAL9& out)
{
	assert(index >= 0 && index < materialNum);
	out = materials[index];
}

/**************************************
マテリアルカラー設定処理
***************************************/
void MeshContainer::SetMaterialColor(const D3DXCOLOR& color, UINT index)
{
	assert(index >= 0 && index < materialNum);

	materials[index].Diffuse = color;

}

/**************************************
マテリアルアルファ設定処理
***************************************/
void MeshContainer::SetMaterialAlpha(float alpha, UINT index)
{
	assert(index >= 0 && index < materialNum);
	materials[index].Diffuse.a = alpha;
}

/**************************************
ワイヤーフレーム用パラメータ設定処理
***************************************/
void MeshContainer::SetWireframePara()
{
	TotalSurfaceNum = mesh->GetNumFaces();
	MeshFVF = mesh->GetFVF();
	mesh->GetVertexBuffer(&VertexBuffer);
	mesh->GetIndexBuffer(&IndexBuffer);
}

/**************************************
リソース開放処理
***************************************/
void MeshContainer::ReleaseResource()
{
	SAFE_RELEASE(mesh);

	for (DWORD i = 0; i < materialNum; i++)
	{
		SAFE_RELEASE(textures[i]);
	}

	materials.clear();

	materialNum = 0;

	if (resource != NULL)
	{
		resource->OnRelease();
		resource = NULL;
	}
}
