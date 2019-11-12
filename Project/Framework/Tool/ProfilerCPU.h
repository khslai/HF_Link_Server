//=====================================
//
//�e���v���[�g�w�b�_[ProfilerCPU.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PROFILERCPU_H_
#define _PROFILERCPU_H_

#include "..\..\main.h"
#include "..\Pattern\BaseSingleton.h"

#include <unordered_map>
#include <chrono>

class ProfilerNode;
/**************************************
�}�N����`
***************************************/
#define USE_PROFILER_CPU

/**************************************
�v���t�@�C���N���X
***************************************/
class ProfilerCPU : public BaseSingleton<ProfilerCPU>
{
	friend class BaseSingleton<ProfilerCPU>;
public:
	void Update();
	void Draw();
	void Clear();
	
	void BeginLabel(const char* labe);
	void EndLabel();

	void Begin(const char* tag);
	void End(const char* tag);

private:
	std::unordered_map<std::string, std::unordered_map<std::string, ProfilerNode>> profilerMap;
	
	std::chrono::system_clock::time_point time, prevTime;
	std::chrono::milliseconds::rep cntFPS;
	DWORD cntFrame;

	std::string currentLabel, prevLabel;

	void CalcElapsed();
	
	ProfilerCPU();
	ProfilerCPU(const ProfilerCPU&) {}
	~ProfilerCPU() {}
};

/**************************************
�v���t�@�C���m�[�h�N���X
***************************************/
class ProfilerNode
{
public:
	ProfilerNode();

	void Count(bool isStart);
	void CalcElapsed(const LARGE_INTEGER& frequency);
	double GetElapsed();

private:
	LARGE_INTEGER start, end;
	double elapsedTime;
};

#endif