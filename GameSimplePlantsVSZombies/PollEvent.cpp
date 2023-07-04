#include "PollEvent.h"
#include <SDL.h>
#include "Game.h"

PollEvent::PollEvent()
{
}

PollEvent::~PollEvent()
{
	//析构容器中所有输入设备对象
	for (auto& item : inputDevices)
		delete item;
}

void PollEvent::AddInputDevice(BasicInputDevice* inputDevice)
{
	if (inputDevice != nullptr)
	{
		inputDevices.emplace_back(inputDevice);
		inputDevice->Initialize();		//添加时顺便将它初始化
	}
}

void PollEvent::SetEventCallback(int eventcode, std::function<void()> fun)
{
	eventsCallback[eventcode] = fun;
}

void PollEvent::Update()
{
	SDL_Event sdlEvent;

	//为所有输入设备执行更新前处理
	for (auto it = inputDevices.begin(); it != inputDevices.end(); it++)
		(*it)->PrepareForUpdate();

	//消息泵循环读取
	while (SDL_PollEvent(&sdlEvent))
	{
		//SDL_Log("PollEvent: %d", sdlEvent.type);
		//查找是否有需要响应此事件的回调函数
		auto it = eventsCallback.find(sdlEvent.type);
		if (it != eventsCallback.end())
			(it->second)();
	}

	//为所有输入设备执行更新
	for (auto it = inputDevices.begin(); it != inputDevices.end(); it++)
		(*it)->Update();
}
