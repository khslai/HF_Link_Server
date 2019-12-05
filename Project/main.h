//=============================================================================
//
// ���C������ [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

// ���������[�N�����p
//#define _CRTDBG_MAP_ALLOC


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
// windows.h�̒���winsock.h���C���N���[�h����̂�
// WinSock2.h�̃C���N���[�h���Ԃ�Windows.h�̑O����Ȃ��ƃR���p�C���G���[�ɂȂ�
#include <WinSock2.h>	// Network�p
#include <windows.h>
#include "d3dx9.h"
#include "Framework\Core\Transform.h"
#include "Framework\Core\GameObject.h"
#include "Framework\Math\TMath.h"
#include "Framework\Math\Vector3.h"
#include "Framework\Core\Utility.h"

#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include "dinput.h"
#include <tchar.h>
#include <stdio.h>
#include <assert.h>
#include <process.h>	// MultiThread�p

// ���������[�N�����p
//#include <stdlib.h>
//#include <crtdbg.h> 
//#ifdef _DEBUG
//#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW
//#endif

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "ws2_32.lib")	// WinSock�ŕK�v
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �r���{�[�h���_�t�H�[�}�b�g
#define FVF_VERTEX_BILLBOARD	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//�@�}�e���A�����g�p����|���S���t�H�[�}�b�g
#define FVF_VERTEX_MATERIAL		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)

#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

//����A�폜�֘A
#define SAFE_RELEASE(p)				{if(p) {p->Release();	p = NULL;}}
#define SAFE_DELETE(p)				{if(p) {delete(p);		p = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[](p);	p = NULL;}}

// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

// ��L�r���{�[�h�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W0
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_BILLBOARD;

// ��L�}�e���A���|���S���t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_MATERIAL;

//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#else
//#define new new
//#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
LPDIRECT3DTEXTURE9 CreateTextureFromFile(LPSTR szName, LPDIRECT3DDEVICE9 lpD3DDevice);
#endif