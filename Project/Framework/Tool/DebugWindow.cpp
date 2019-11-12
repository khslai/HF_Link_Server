//=====================================
//
//�f�o�b�O�E�B���h�E����[DebugWindow.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "debugWindow.h"
#include "../../Library/imgui/imgui.h"
#include "../../Library/imgui/imgui_impl_win32.h"
#include "../../Library/imgui/imgui_impl_dx9.h"
#include "../Input/input.h"

/**************************************
�}�N����`
***************************************/
#define INTERBAL_GETTIMER		(20)

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
LARGE_INTEGER timeCountBegin;
static unsigned int cntFrame = 0;
static bool enableDraw = true;

/**************************************
�v���g�^�C�v�錾
***************************************/
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/**************************************
�f�o�b�O�E�B���h�E�p�R�[���o�b�N
***************************************/
LRESULT Debug::WindPrcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef USE_DEBUGFUNC
	return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
#else
	return S_OK;
#endif
}

/**************************************
����������
***************************************/
void Debug::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
#ifdef USE_DEBUGFUNC
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	ImGui::StyleColorsDark();
#endif
}

/**************************************
�I������
***************************************/
void Debug::Uninit()
{
#ifdef USE_DEBUGFUNC
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
#endif
}

/**************************************
�X�V����
***************************************/
void Debug::Update(void)
{
#ifdef USE_DEBUGFUNC
	if (Keyboard::GetTrigger(DIK_D) && Keyboard::GetPress(DIK_LCONTROL))
	{
		enableDraw = !enableDraw;
	}

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	cntFrame++;
#endif
}

/**************************************
�`�揈��
***************************************/
void Debug::Draw(void)
{
#ifdef USE_DEBUGFUNC
	if (!enableDraw)
	{
		ImGui::EndFrame();
		return;
	}
	
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif
}

/*************************************
�f�o�b�O�E�B���h�E�J�n����
***************************************/
void Debug::Begin(const char *label, bool menuBar)
{
#ifdef USE_DEBUGFUNC
	ImGuiWindowFlags flag = 0;

	if (menuBar) flag |= ImGuiWindowFlags_MenuBar;

	ImGui::Begin(label, nullptr, flag);
#endif
}

/*************************************
�f�o�b�O�E�B���h�E�I������
***************************************/
void Debug::End()
{
#ifdef USE_DEBUGFUNC
	ImGui::End();
#endif
}

/*************************************
�ėp�f�o�b�O�e�L�X�g�\��
***************************************/
void Debug::Log(const char *str, ...)
{
#ifdef USE_DEBUGFUNC
	Begin("Console");
	va_list ap;
	va_start(ap, str);
	ImGui::TextV(str, ap);
	//ImGui::Text(str, ap);
	va_end(ap);
	End();
#endif
}

/*************************************
�f�o�b�O�e�L�X�g�\������
***************************************/
void Debug::Text(const char *str, ...)
{
#ifdef USE_DEBUGFUNC
	va_list ap;
	va_start(ap, str);
	ImGui::TextV(str, ap);
	//ImGui::Text(str, ap);
	va_end(ap);
#endif
}

/*************************************
�f�o�b�O�e�L�X�g�\������
***************************************/
void Debug::Text(const D3DXVECTOR3& arg, const char* name)
{
#ifdef USE_DEBUGFUNC
	Text("%s : %f %f, %f", name, arg.x, arg.y, arg.z);
#endif
}

/*************************************
�f�o�b�O�{�^���\������
***************************************/
bool Debug::Button(const char *label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::Button(label);
#else
	return false;
#endif
}

/*************************************
���W�I�{�^������
***************************************/
bool Debug::RadioButton(const char* label, int& output, int val)
{
#ifdef USE_DEBUGFUNC
	return ImGui::RadioButton(label, &output, val);
#else
	return false;
#endif
}

/*************************************
�`�F�b�N�{�b�N�X����
***************************************/
bool Debug::CheckBox(const char* label, bool& val)
{
#ifdef USE_DEBUGFUNC
	return ImGui::Checkbox(label, &val);
#else
	return false;
#endif
}

/*************************************
���͏���
***************************************/
bool Debug::Input(const char* label, float& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputFloat(label, &out);
#else
	return false;
#endif
}

/*************************************
���͏���
***************************************/
bool Debug::Input(const char* label, int& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputInt(label, &out);
#else
	return false;
#endif
}

/*************************************
���͏���
***************************************/
bool Debug::Input(const char* label, char* out, size_t sizeBuff)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputText(label, out, sizeBuff);
#else
	return false;
#endif
}

/*************************************
���͏���
***************************************/
bool Debug::Input(const char* label, D3DXVECTOR3& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputFloat3(label, (float*)&out);
#else
	return false;
#endif
}

/*************************************
���͏���
***************************************/
bool Debug::Input(const char* label, D3DXVECTOR2& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputFloat2(label, (float*)&out);
#else
	return false;
#endif
}

/*************************************
���͏���
***************************************/
bool Debug::Input(const char* label, std::string& out)
{
#ifdef USE_DEBUGFUNC
	char tmp[128];
	strcpy(tmp, out.c_str());
	bool res = ImGui::InputText(label, tmp, 128);
	if (res)
	{
		out = std::string(tmp);
	}
	return res;
#else
	return false;
#endif
}

/*************************************
�f�o�b�O�X���C�_�[����
***************************************/
bool Debug::Slider(const char *label, float& adr, float min, float max)
{
#ifdef USE_DEBUGFUNC
	return ImGui::SliderFloat(label, &adr, min, max);

#else
	return false;
#endif
}

/*************************************
�f�o�b�O�X���C�_�[����
***************************************/
bool Debug::Slider(const char* label, int& out, int min, int max)
{
#ifdef USE_DEBUGFUNC
	return ImGui::SliderInt(label, &out, min, max);
#else
	return false;
#endif
}

/*************************************
�f�o�b�O�X���C�_�[����
***************************************/
bool Debug::Slider(const char* label, D3DXVECTOR3& out, const D3DXVECTOR3& min, const D3DXVECTOR3& max)
{
#ifdef USE_DEBUGFUNC
	bool res = false;
	res |= ImGui::SliderFloat((std::string(label) + std::string(".x")).c_str(), &out.x, min.x, max.x);
	res |= ImGui::SliderFloat((std::string(label) + std::string(".y")).c_str(), &out.y, min.y, max.y);
	res |= ImGui::SliderFloat((std::string(label) + std::string(".z")).c_str(), &out.z, min.z, max.z);
	return res;
#else
	return false;
#endif
}

/*************************************
�f�o�b�O�X���C�_�[����
***************************************/
bool Debug::Slider(const char* label, D3DXVECTOR2& out, const D3DXVECTOR2& min, const D3DXVECTOR2& max)
{
#ifdef USE_DEBUGFUNC
	bool res = false;
	res |= ImGui::SliderFloat((std::string(label) + std::string(".x")).c_str(), &out.x, min.x, max.x);
	res |= ImGui::SliderFloat((std::string(label) + std::string(".y")).c_str(), &out.y, min.x, max.y);
	return res;
#else
	return false;
#endif
}

/*************************************
�f�o�b�O�J���[�s�b�J�[����
***************************************/
bool Debug::ColorEdit(const char *label, D3DXCOLOR& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::ColorEdit4(label, (float*)&out);
#else
	return false;
#endif
}

/*************************************
�e�N�X�`���\������
***************************************/
void Debug::DrawTexture(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2& size)
{
#ifdef USE_DEBUGFUNC
	ImGui::Image((void*)texture, ImVec2(size.x, size.y));
#endif
}


/*************************************
�v���O���X�o�[����
***************************************/
void Debug::ProgressBar(const char* label, float fraction, const D3DXVECTOR2& size)
{
#ifdef USE_DEBUGFUNC
	ImGui::ProgressBar(fraction, ImVec2(size.x, size.y), label);
#endif
}

/*************************************
�f�o�b�O�E�B���h�E���s����
***************************************/
void Debug::NewLine(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::NewLine();
#endif
}

/*************************************
�f�o�b�O�E�B���h�E�A���s����
***************************************/
void Debug::SameLine(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::SameLine();
#endif
}

/*************************************
�c���[�\���W�J����
***************************************/
void Debug::ExpandTree(bool isOpen)
{
#ifdef USE_DEBUGFUNC
	ImGui::SetNextTreeNodeOpen(isOpen, ImGuiSetCond_Once);
#endif
}

/*************************************
�c���[�\���v�b�V������
***************************************/
bool Debug::PushTree(const char *label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::TreeNode(label);
#else
	return  false;
#endif
}

/*************************************
�c���[�\���|�b�v����
***************************************/
void Debug::PopTree(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::TreePop();
#endif
}

/*************************************
���j���[�o�[�ݒ�J�n����
***************************************/
bool Debug::BeginMenu()
{
#ifdef USE_DEBUGFUNC
	return ImGui::BeginMenuBar();
#else
	return false;
#endif
}

/*************************************
���j���[�o�[�ݒ�I������
***************************************/
void Debug::EndMenu()
{
#ifdef USE_DEBUGFUNC
	ImGui::EndMenuBar();
#endif
}

/*************************************
���j���[�ݒ�I������
***************************************/
bool Debug::BeginMenuItem(const char* label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::BeginMenu(label);
#else
	return false;
#endif
}

/*************************************
���j���[�ݒ�I������
***************************************/
void Debug::EndMenuItem()
{
#ifdef  USE_DEBUGFUNC
	ImGui::EndMenu();
#endif //  USE_DEBUGFUNC

}

/*************************************
�q���J�n����
***************************************/
bool Debug::BeginChild(const char* id)
{
#ifdef USE_DEBUGFUNC
	return ImGui::BeginChild(ImGui::GetID((void*)0));
#else
	return false;
#endif
}

/*************************************
�q���I������
***************************************/
void Debug::EndChild()
{
#ifdef USE_DEBUGFUNC
	ImGui::EndChild();
#endif
}

///**************************************
//���𑜓x�^�C�}�[�ł̌v���J�n����
//***************************************/
//void BeginTimerCount(void)
//{
//#ifdef USE_DEBUGFUNC
//	QueryPerformanceCounter(&timeCountBegin);
//#endif
//}
//
///**************************************
//�v���J�n����̌o�ߎ���[�P�ʁFmsec]
//***************************************/
//double GetProgressTimerCount(void)
//{
//#ifdef USE_DEBUGFUNC
//	//�^�C�}�[�̎��g�����擾
//	LARGE_INTEGER frequencyTimer;
//	QueryPerformanceFrequency(&frequencyTimer);
//
//	//�J�E���g�擾
//	LARGE_INTEGER timeCurrent;
//	QueryPerformanceCounter(&timeCurrent);
//
//	//�v���J�n����̌o�ߎ���[msec]���v�Z
//	LONGLONG span = timeCurrent.QuadPart - timeCountBegin.QuadPart;
//	double msec = (double)span * 1000 / (double)frequencyTimer.QuadPart;
//
//	return msec;
//#else 
//	return 0.0f;
//#endif
//}
//
///**************************************
//�^�C�}�[�J�E���g�擾�����i20�t���[�������ɓ���j
//***************************************/
//void GetTimerCount(LARGE_INTEGER *ptr)
//{
//#ifdef	USE_DEBUGFUNC
//	if (cntFrame % INTERBAL_GETTIMER != 0)
//		return;
//
//	QueryPerformanceCounter(ptr);
//#endif
//}
//
///**************************************
//�o�ߎ��Ԏ擾����[msec]
//***************************************/
//double CalcProgressTime(LARGE_INTEGER start, LARGE_INTEGER end)
//{
//#ifdef USE_DEBUGFUNC
//	//�^�C�}�[�̎��g���擾
//	LARGE_INTEGER frequency;
//	QueryPerformanceFrequency(&frequency);
//
//	//�o�ߎ��Ԃ��v�Z
//	LONGLONG span = end.QuadPart - start.QuadPart;
//	double msec = (double)span * 1000.0f / (double)frequency.QuadPart;
//
//	return msec;
//#else
//	return 0.0f;
//#endif
//}
