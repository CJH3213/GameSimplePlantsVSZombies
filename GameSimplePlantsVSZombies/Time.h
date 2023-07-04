#pragma once
#include <SDL.h>

class Time
{
private:

	//从游戏开始的时间，不受暂停影响
	static Uint32 realtimeSinceStartup;
	//从游戏开始的时间，受暂停、缩放影响
	static Uint32 time;
	//从游戏开始的总帧数
	static Uint32 frameCount;
	//从场景开始的时间，受暂停、缩放影响
	static Uint32 timeSinceLevelLoad;

	//时间缩放比例，（1为正常速率，小于1为变慢，大于1为变快）
	static float timeScale;
	//调用FixedUpdate方法的固定间隔时长
	static float fixedDeltaTime;

	//上一帧时的时间
	static Uint32 lastFrameTicks;
	//两帧时间间隔，单位1秒（1.0f = 1S），会受时间缩放比影响
	static float deltaTime;
	//两帧时间间隔，不受时间缩放比影响
	static float unscaleDeltaTime;

public:
	//初始化
	static inline void Init()
	{
		timeScale = 1.0f;		//初始缩放时间为1倍
		fixedDeltaTime = 0.02f;		//固定更新间隔为20ms

		lastFrameTicks = SDL_GetTicks();
	}

	// 获取毫秒值时间，从游戏开始至今
	static inline uint32_t Time_ms()
	{
		return SDL_GetTicks();
	}

	// 获取秒值时间，从游戏开始至今
	static inline float Time_s()
	{
		return (float)SDL_GetTicks() / 1000.0f;
	}

	////获取从游戏开始至今的时间，不受暂停影响
	//static inline Uint32 GetRealtimeSinceStartup()
	//{
	//	return SDL_GetTicks();
	//}

	////清零场景时长，该函数在场景的Start()被调用
	//static inline void ClearTimeSinceLevelLoad()
	//{
	//	timeSinceLevelLoad = 0;
	//}

	////每帧更新
	//static inline void UpdateTimePerFrame()
	//{
	//	//更新两帧间隔
	//	unscaleDeltaTime = (SDL_GetTicks() - lastFrameTicks) / 1000;
	//	lastFrameTicks = SDL_GetTicks();
	//	deltaTime = unscaleDeltaTime * timeScale;

	//	//更新游戏时长
	//	realtimeSinceStartup += unscaleDeltaTime;
	//	time += deltaTime;
	//	timeSinceLevelLoad += deltaTime;
	//	//更新总帧数量
	//	frameCount++;
	//}
	////获取帧间隔时长
	//static inline float GetDeltaTime()
	//{
	//	return deltaTime;
	//}
	////获取不缩放的帧间隔时长
	//static inline float GetUnscaleDeltaTime()
	//{
	//	return unscaleDeltaTime;
	//}

	////获取固定更新间隔时长，会受
	//static inline float GetFixedDeltaTime()
	//{
	//	return fixedDeltaTime * timeScale;
	//}
};

