#pragma once
#include <unordered_map>
#include <functional>
#include <string>

/// <summary>
/// ֻ��һ��ģ�����T���㴫�뺯�����ͣ�������Ҫ�ֿ�����ֵ��ÿ��������д����
/// ͬʱ��ģ����ֻ������û��ʵ�֣��Ƿ�ֹ���뺯����������ͣ�
/// 1.�����뺯������ʱ��������������汾��⺯���ķ���ֵ�Ͳ�������
/// 2.�������Ǻ�������ʱ������Ϊû��ʵ�ֶ�������������ʹ�ò����������͡�
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class EventHandlers;


/// <summary>
/// ������ģ���࣬��⴫��ĺ�������
/// RΪ��������ֵ���ͣ�ArgsΪ����������
/// </summary>
/// <typeparam name="R"></typeparam>
/// <typeparam name="...Args"></typeparam>
template<class R, typename... Args>
class EventHandlers<R(Args...)>
{
private:
	// ���лص�����������
	std::unordered_map<std::string, std::function<R(Args...)>> mHandlers;

public:
	// ��Ӽ����¼�
	bool AddListener(std::string mesTag, const std::function<R(Args...)>& func);
	// �Ƴ������¼�
	bool RemoveListener(std::string mesTag);
	// ִ�������¼��ص�
	void InvokeAll(Args... args);
};

template<class R, typename ...Args>
inline bool EventHandlers<R(Args...)>::AddListener(std::string mesTag, const std::function<R(Args...)>& func)
{
	// δע�����ΪmesTag���¼���ע����¼�
	if (mHandlers.count(mesTag) <= 0)
	{
		mHandlers.emplace(mesTag, func);
		return true;
	}
	// ͬ���¼���ע��
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
