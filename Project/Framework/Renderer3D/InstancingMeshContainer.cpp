//=====================================
//
//�C���X�^���V���O���b�V���R���e�i����[InstancingMeshContainer.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "InstancingMeshContainer.h"
#include "../Effect/InstancingMeshEffect.h"

/**************************************
�R���X�g���N�^
***************************************/
InstancingMeshContainer::InstancingMeshContainer(unsigned MaxNum) :
	MaxInstance(MaxNum),
	vtxBuff(nullptr),
	indexBuff(nullptr),
	declare(nullptr),
	transformBuffer(nullptr),
	effect(nullptr),
	pWorld(nullptr)
{
	effect = new InstancingMeshEffect();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//SRT�o�b�t�@���쐬
	pDevice->CreateVertexBuffer(sizeof(D3DXMATRIX) * MaxNum, 0, 0, D3DPOOL_MANAGED, &transformBuffer, 0);
}

/**************************************
�f�X�g���N�^
***************************************/
InstancingMeshContainer::~InstancingMeshContainer()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(declare);
	
	for (unsigned i = 0; i < textures.size(); i++)
	{
		SAFE_RELEASE(textures[i]);
	}
	textures.clear();

	SAFE_DELETE(effect);
}

/**************************************
�ǂݍ��ݏ���
***************************************/
void InstancingMeshContainer::Load(const std::string& path)
{
	LPD3DXMESH mesh;
	LPD3DXBUFFER buffer;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���b�V���ǂݍ���
	D3DXLoadMeshFromX(path.c_str(),
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&buffer,
		NULL,
		&numMaterial,
		&mesh);

	//�אڏ��쐬
	std::vector<DWORD> adjList;
	adjList.resize(3 * mesh->GetNumFaces());
	mesh->GenerateAdjacency(1.0f / 512, &adjList[0]);

	//���b�V�����œK��
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, &adjList[0], 0, 0, 0);

	//�e�o�b�t�@���擾
	mesh->GetVertexBuffer(&vtxBuff);
	mesh->GetIndexBuffer(&indexBuff);
	fvf = mesh->GetFVF();

	//�����e�[�u�����擾
	attributeTable.resize(numMaterial);
	mesh->GetAttributeTable(&attributeTable[0], NULL);

	//���_�錾���쐬
	MakeDeclaration(mesh);

	//�}�e���A���]��
	materials.resize(numMaterial);
	D3DXMATERIAL *matBuffer = (D3DXMATERIAL*)buffer->GetBufferPointer();
	for (DWORD i = 0; i < numMaterial; i++)
	{
		materials[i] = matBuffer[i].MatD3D;
	}

	//�e�N�X�`���ǂݍ���
	textures.resize(numMaterial, NULL);
	const std::string DirectoryName = path.substr(0, path.find_last_of('/'));
	for (DWORD i = 0; i < numMaterial; i++)
	{
		if (matBuffer[i].pTextureFilename == NULL)
			continue;

		std::string fileName = DirectoryName + "/" + std::string(matBuffer[i].pTextureFilename);
		D3DXCreateTextureFromFile(pDevice, fileName.c_str(), &textures[i]);
	}

	SAFE_RELEASE(buffer);
	SAFE_RELEASE(mesh);
}

/**************************************
�`�揈��
***************************************/
void InstancingMeshContainer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�錾�Ɗe�o�b�t�@���Z�b�g
	pDevice->SetVertexDeclaration(declare);

	pDevice->SetStreamSource(0, vtxBuff, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetStreamSource(1, transformBuffer, 0, sizeof(D3DXMATRIX));
	pDevice->SetIndices(indexBuff);

	//�X�g���[���\�[�X���g���ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | indexTransform);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�}�e���A�����Ƃɕ`��
	for (unsigned i = 0; i < numMaterial; i++)
	{
		effect->SetMaterial(materials[i]);

		pDevice->SetTexture(0, textures[i]);

		effect->Begin();
		effect->BeginPass(0);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0,
			attributeTable[i].VertexStart,
			attributeTable[i].VertexCount,
			attributeTable[i].VertexStart * 3,
			attributeTable[i].FaceCount);

		effect->EndPass();
		effect->End();
	}

	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
}


/**************************************
SRT�o�b�t�t�@���b�N����
***************************************/
void InstancingMeshContainer::Lock()
{
	assert(pWorld == nullptr);
	indexTransform = 0;
	transformBuffer->Lock(0, 0, (void**)&pWorld, 0);
}

/**************************************
SRT�A�����b�N����
***************************************/
void InstancingMeshContainer::Unlock()
{
	assert(pWorld != nullptr);
	transformBuffer->Unlock();
	pWorld = nullptr;
}

/**************************************
SRT��񖄂ߍ��ݏ���
***************************************/
bool InstancingMeshContainer::EmbedTranform(const Transform & transform)
{
	if (indexTransform >= MaxInstance)
		return false;

	*pWorld = transform.GetMatrix();
	
	pWorld++;
	indexTransform++;

	return true;
}

/**************************************
���_�錾�쐬
***************************************/
void InstancingMeshContainer::MakeDeclaration(LPD3DXMESH mesh)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVERTEXELEMENT9 elem[65];
	ZeroMemory(&elem[0], sizeof(D3DVERTEXELEMENT9) * 65);
	mesh->GetDeclaration(elem);

	for (int i = 0; i < 65; i++)
	{
		if (elem[i].Type != D3DDECLTYPE_UNUSED)
			continue;

		elem[i] = D3DVERTEXELEMENT9{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 };
		elem[i + 1] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 4, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 };
		elem[i + 2] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 8, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 };
		elem[i + 3] = D3DVERTEXELEMENT9{ 1, sizeof(float) * 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 };
		elem[i + 4] = D3DDECL_END();
		break;
	}

	pDevice->CreateVertexDeclaration(elem, &declare);
}
