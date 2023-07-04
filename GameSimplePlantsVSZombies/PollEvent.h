#pragma once
#include "BasicInputDevice.h"
#include <vector>
#include <map>
#include <functional>

class PollEvent
{
private:
	//持有者
	class Game* owner = nullptr;
	//输入设备集合
	std::vector<BasicInputDevice*> inputDevices;
	//事件回调集合（回调函数无参数无返回值）
	std::map<int, std::function<void()>> eventsCallback;

public:

	//获取指定类型的输入设备对象
	template<class T>
	BasicInputDevice* GetInputDevice();

	//构造函数
	PollEvent();
	//析构
	~PollEvent();

	//添加输入设备对象
	void AddInputDevice(BasicInputDevice* inputDevice);

	//添加事件回调函数
	void SetEventCallback(int eventcode, std::function<void()> fun);

	//更新消息
	void Update();
};

/// <summary>
/// 获取容器中指定类型的输入设备对象
/// </summary>
/// <typeparam name="T">传入目标输入对象类的类型</typeparam>
/// <returns></returns>
template<class T>
inline BasicInputDevice* PollEvent::GetInputDevice()
{
	for (auto it = inputDevices.begin(); it != inputDevices.end(); it++)
	{
		if (typeid(T).name == (*it)->GetClassInfo().name())
		{
			return dynamic_cast<T*> (*it);  //向下转换类型
		}
	}
	return nullptr;
}
