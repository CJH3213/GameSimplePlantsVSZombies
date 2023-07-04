#pragma once
#include <SDL.h>

class Time
{
private:

	//����Ϸ��ʼ��ʱ�䣬������ͣӰ��
	static Uint32 realtimeSinceStartup;
	//����Ϸ��ʼ��ʱ�䣬����ͣ������Ӱ��
	static Uint32 time;
	//����Ϸ��ʼ����֡��
	static Uint32 frameCount;
	//�ӳ�����ʼ��ʱ�䣬����ͣ������Ӱ��
	static Uint32 timeSinceLevelLoad;

	//ʱ�����ű�������1Ϊ�������ʣ�С��1Ϊ����������1Ϊ��죩
	static float timeScale;
	//����FixedUpdate�����Ĺ̶����ʱ��
	static float fixedDeltaTime;

	//��һ֡ʱ��ʱ��
	static Uint32 lastFrameTicks;
	//��֡ʱ��������λ1�루1.0f = 1S��������ʱ�����ű�Ӱ��
	static float deltaTime;
	//��֡ʱ����������ʱ�����ű�Ӱ��
	static float unscaleDeltaTime;

public:
	//��ʼ��
	static inline void Init()
	{
		timeScale = 1.0f;		//��ʼ����ʱ��Ϊ1��
		fixedDeltaTime = 0.02f;		//�̶����¼��Ϊ20ms

		lastFrameTicks = SDL_GetTicks();
	}

	// ��ȡ����ֵʱ�䣬����Ϸ��ʼ����
	static inline uint32_t Time_ms()
	{
		return SDL_GetTicks();
	}

	// ��ȡ��ֵʱ�䣬����Ϸ��ʼ����
	static inline float Time_s()
	{
		return (float)SDL_GetTicks() / 1000.0f;
	}

	////��ȡ����Ϸ��ʼ�����ʱ�䣬������ͣӰ��
	//static inline Uint32 GetRealtimeSinceStartup()
	//{
	//	return SDL_GetTicks();
	//}

	////���㳡��ʱ�����ú����ڳ�����Start()������
	//static inline void ClearTimeSinceLevelLoad()
	//{
	//	timeSinceLevelLoad = 0;
	//}

	////ÿ֡����
	//static inline void UpdateTimePerFrame()
	//{
	//	//������֡���
	//	unscaleDeltaTime = (SDL_GetTicks() - lastFrameTicks) / 1000;
	//	lastFrameTicks = SDL_GetTicks();
	//	deltaTime = unscaleDeltaTime * timeScale;

	//	//������Ϸʱ��
	//	realtimeSinceStartup += unscaleDeltaTime;
	//	time += deltaTime;
	//	timeSinceLevelLoad += deltaTime;
	//	//������֡����
	//	frameCount++;
	//}
	////��ȡ֡���ʱ��
	//static inline float GetDeltaTime()
	//{
	//	return deltaTime;
	//}
	////��ȡ�����ŵ�֡���ʱ��
	//static inline float GetUnscaleDeltaTime()
	//{
	//	return unscaleDeltaTime;
	//}

	////��ȡ�̶����¼��ʱ��������
	//static inline float GetFixedDeltaTime()
	//{
	//	return fixedDeltaTime * timeScale;
	//}
};

