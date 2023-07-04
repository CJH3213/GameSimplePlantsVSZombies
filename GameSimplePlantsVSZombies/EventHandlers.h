#pragma once
#include <unordered_map>
#include <functional>
#include <string>

/// <summary>
/// 只有一个模板参数T方便传入函数类型，而不需要分开返回值和每个参数的写法；
/// 同时该模板类只有声明没有实现，是防止传入函数以外的类型，
/// 1.当传入函数类型时，会调用特例化版本拆解函数的返回值和参数包，
/// 2.如果传入非函数类型时，会因为没有实现而报错：“不允许使用不完整的类型”
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class EventHandlers;


/// <summary>
/// 特例化模板类，拆解传入的函数类型
/// R为函数返回值类型，Args为函数参数包
/// </summary>
/// <typeparam name="R"></typeparam>
/// <typeparam name="...Args"></typeparam>
template<class R, typename... Args>
class EventHandlers<R(Args...)>
{
private:
	// 持有回调函数的容器
	std::unordered_map<std::string, std::function<R(Args...)>> mHandlers;

public:
	// 添加监听事件
	bool AddListener(std::string mesTag, const std::function<R(Args...)>& func);
	// 移除监听事件
	bool RemoveListener(std::string mesTag);
	// 执行所有事件回调
	void InvokeAll(Args... args);
};

template<class R, typename ...Args>
inline bool EventHandlers<R(Args...)>::AddListener(std::string mesTag, const std::function<R(Args...)>& func)
{
	// 未注册过名为mesTag的事件，注册该事件
	if (mHandlers.count(mesTag) <= 0)
	{
		mHandlers.emplace(mesTag, func);
		return true;
	}
	// 同名事件已注册
	return false;
}

template<class R, typename ...Args>
inline bool EventHandlers<R(Args...)>::RemoveListener(std::string mesTag)
{
	auto it = mHandlers.find(mesTag);
	if (it != mHandlers.end())
	{
		mHandlers.erase(it);
		return true;
	}

	return false;
}

template<class R, typename ...Args>
inline void EventHandlers<R(Args...)>::InvokeAll(Args... args)
{
	for (auto func : mHandlers)
	{
		func.second(args...);
	}
}
