//=====================================
//
//�e���v���[�g����[template.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ProfilerCPU.h"
#include "DebugWindow.h"

#include <string.h>
#include <assert.h>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define PROFILER_CPU_COUNT_INTERBAL		(20)
#define PROFILER_CPU_BAR_SIZE			(D3DXVECTOR2(75.0f, 0.0f))
#define PROFILER_LABEL_DEFAULT			"Profiler"

/**************************************
Profiler�R���X�g���N�^
***************************************/
ProfilerCPU::ProfilerCPU()
{
	currentLabel = prevLabel = string(PROFILER_LABEL_DEFAULT);
}

/**************************************
ProfilerCPU�X�V����
***************************************/
void ProfilerCPU::Update()
{
#ifdef USE_PROFILER_CPU
	if (cntFrame % PROFILER_CPU_COUNT_INTERBAL == 0)
	{
		prevTime = time;
		time = std::chrono::system_clock::now();

		std::chrono::milliseconds deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(time - prevTime);
		std::chrono::milliseconds frame = std::chrono::milliseconds(PROFILER_CPU_COUNT_INTERBAL * 1000);
		cntFPS = frame / deltaTime;
	}

	Debug::Log("FPS:%d", cntFPS);
	cntFrame = Math::WrapAround(0, PROFILER_CPU_COUNT_INTERBAL, ++cntFrame);
#endif
}

/**************************************
�`�揈��
***************************************/
void ProfilerCPU::Draw()
{
#ifdef USE_PROFILER_CPU
	CalcElapsed();

	for (auto&& profiler : profilerMap)
	{
		Debug::Begin(profiler.first.c_str());

		//FPS�\��
		Debug::Log("FPS:%d", cntFPS);

		//���o�ߎ��ԕ\��
		double progress = 0.0;
		for (auto&& nodeMap : profiler.second)
		{
			progress += nodeMap.second.GetElapsed();
		}
		Debug::Text("%3f[msec]", progress);

		//�e�m�[�h�\��
		for (auto&& nodeMap : profiler.second)
		{
			double elapsed = nodeMap.second.GetElapsed();
			Debug::ProgressBar(NULL, (float)(elapsed / progress), PROFILER_CPU_BAR_SIZE);
			Debug::SameLine();
			Debug::Text("%s : %3f[msec]", nodeMap.first.c_str(), elapsed);
		}

		Debug::End();
	}
#endif
}

/**************************************
�N���A����
***************************************/
void ProfilerCPU::Clear()
{
	for (auto&& nodeMap : profilerMap)
	{
		nodeMap.second.clear();
	}
	profilerMap.clear();

	cntFrame = 0;
}

/**************************************
���x���J�n����
***************************************/
void ProfilerCPU::BeginLabel(const char* label)
{
#ifdef USE_PROFILER_CPU
	prevLabel = currentLabel;
	currentLabel = string(label);
#endif
}

/**************************************
���x���I������
***************************************/
void ProfilerCPU::EndLabel()
{
#ifdef USE_PROFILER_CPU
	currentLabel = prevLabel;
#endif
}

/**************************************
�v���J�n����
***************************************/
void ProfilerCPU::Begin(const char* tag)
{
#ifdef USE_PROFILER_CPU
	if (cntFrame % PROFILER_CPU_COUNT_INTERBAL != 0)
		return;

	profilerMap[currentLabel][string(tag)].Count(true);
#endif
}

/**************************************
�v���I������
***************************************/
void ProfilerCPU::End(const char* tag)
{
#ifdef USE_PROFILER_CPU
	if (cntFrame % PROFILER_CPU_COUNT_INTERBAL != 0)
		return;

	profilerMap[currentLabel][string(tag)].Count(false);
#endif
}

/**************************************
�o�ߎ��Ԍv�Z
***************************************/
void ProfilerCPU::CalcElapsed()
{
#ifdef USE_PROFILER_CPU
	LARGE_INTEGER frequencty;
	QueryPerformanceFrequency(&frequencty);

	for (auto&& profiler : profilerMap)
	{
		for (auto&& node : profiler.second)
		{
			node.second.CalcElapsed(frequencty);
		}
	}
#endif
}

/**************************************
ProfilerNode�R���X�g���N�^
***************************************/
ProfilerNode::ProfilerNode()
{
	ZeroMemory(&start, sizeof(start));
	ZeroMemory(&end, sizeof(end));
	elapsedTime = 0.0;
}

/**************************************
ProfilerNode�J�E���g����
***************************************/
void ProfilerNode::Count(bool isStart)
{
	if (isStart)
	{
		QueryPerformanceCounter(&start);
	}
	else
	{
		QueryPerformanceCounter(&end);
	}
}

/**************************************
ProfilerNode�o�ߎ��Ԍv�Z����
***************************************/
void ProfilerNode::CalcElapsed(const LARGE_INTEGER& frequency)
{
	LONGLONG span = end.QuadPart - start.QuadPart;
	elapsedTime = (double)span * 1000.0 / (double)frequency.QuadPart;
}
/**************************************
ProfilerNode�o�ߎ��Ԏ擾����
***************************************/
double ProfilerNode::GetElapsed()
{
	return elapsedTime;
}