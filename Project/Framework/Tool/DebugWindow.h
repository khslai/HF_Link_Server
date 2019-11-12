//=====================================
//
//�f�o�b�O�E�B���h�E�w�b�_[debugWindow.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DEBUGWINDOW_H_
#define _DEBUGWINDOW_H_

#include "../../main.h"

#include <string>

/**************************************
�}�N����`
***************************************/
#define USE_DEBUGFUNC
#define STR(var) #var		//var�𕶎���ɒu������}�N��

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************/
//ImGUI���b�p�[�N���X
/***************************************/
class Debug
{
public:
	//�J�n�A�I������
	static void Begin(const char* label, bool menuBar = false);
	static void End();

	//Console�\��
	static void Log(const char *str, ...);

	//�e�L�X�g�\��
	static void Text(const char* str, ...);
	static void Text(const D3DXVECTOR3& arg, const char* name);

	//�{�^�����͊֘A
	static bool Button(const char* label);
	static bool RadioButton(const char* label, int& out, int val);
	static bool CheckBox(const char* label, bool& val);
	
	//�p�����[�^���͊֘A
	static bool Input(const char* label, float& out);
	static bool Input(const char* label, int& out);
	static bool Input(const char* label, char* out, size_t sizeBuff);
	static bool Input(const char* label, D3DXVECTOR3& out);
	static bool Input(const char* label, D3DXVECTOR2& out);
	static bool Input(const char* label, std::string& out);

	//�p�����[�^�X���C�_�[���͊֘A
	static bool Slider(const char* label, float& out, float min, float max);
	static bool Slider(const char* label, int& out, int min, int max);
	static bool Slider(const char* label, D3DXVECTOR3& out, const D3DXVECTOR3& min, const D3DXVECTOR3& max);
	static bool Slider(const char* label, D3DXVECTOR2& out, const D3DXVECTOR2& min, const D3DXVECTOR2& max);

	//�e�N�X�`���`��
	static void DrawTexture(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2& size);

	//�J���[�G�f�B�^
	static bool ColorEdit(const char* label, D3DXCOLOR& out);
	
	//�v���O���X�o�[
	static void ProgressBar(const char* label, float fraction, const D3DXVECTOR2& size = D3DXVECTOR2(-1.0f, 0.0f));

	//���s�A���s
	static void NewLine();
	static void SameLine();

	//�c���[�֘A
	static void ExpandTree(bool isOpen);
	static bool PushTree(const char* label);
	static void PopTree();

	//���j���[�o�[�֘A
	static bool BeginMenu();
	static void EndMenu();
	static bool BeginMenuItem(const char* label);
	static void EndMenuItem();
	template <class T>
	static void MenuItem(const char* label, T func)
	{
#ifdef USE_DEBUGFUNC
		if (ImGui::MenuItem(label))
		{
			func();
		}
#endif
	}

	//�q�v�f�֘A
	static bool BeginChild(const char* label);
	static void EndChild();

	//�e�폈��
	static LRESULT WindPrcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	static void Uninit();
	static void Update();
	static void Draw();

private:
	Debug();
};

#endif