#include "PollEvent.h"
#include <SDL.h>
#include "Game.h"

PollEvent::PollEvent()
{
}

PollEvent::~PollEvent()
{
	//�������������������豸����
	for (auto& item : inputDevices)
		delete item;
}

void PollEvent::AddInputDevice(BasicInputDevice* inputDevice)
{
	if (inputDevice != nullptr)
	{
		inputDevices.emplace_back(inputDevice);
		inputDevice->Initialize();		//���ʱ˳�㽫����ʼ��
	}
}

void PollEvent::SetEventCallback(int eventcode, std::function<void()> fun)
{
	eventsCallback[eventcode] = fun;
}

void PollEvent::Update()
{
	SDL_Event sdlEvent;

	//Ϊ���������豸ִ�и���ǰ����
	for (auto it = inputDevices.begin(); it != inputDevices.end(); it++)
		(*it)->PrepareForUpdate();

	//��Ϣ��ѭ����ȡ
	while (SDL_PollEvent(&sdlEvent))
	{
		//SDL_Log("PollEvent: %d", sdlEvent.type);
		//�����Ƿ�����Ҫ��Ӧ���¼��Ļص�����
		auto it = eventsCallback.find(sdlEvent.type);
		if (it != eventsCallback.end())
			(it->second)();
	}

	//Ϊ���������豸ִ�и���
	for (auto it = inputDevices.begin(); it != inputDevices.end(); it++)
		(*it)->Update();
}
