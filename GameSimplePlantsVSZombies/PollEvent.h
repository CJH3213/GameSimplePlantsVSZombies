#pragma once
#include "BasicInputDevice.h"
#include <vector>
#include <map>
#include <functional>

class PollEvent
{
private:
	//������
	class Game* owner = nullptr;
	//�����豸����
	std::vector<BasicInputDevice*> inputDevices;
	//�¼��ص����ϣ��ص������޲����޷���ֵ��
	std::map<int, std::function<void()>> eventsCallback;

public:

	//��ȡָ�����͵������豸����
	template<class T>
	BasicInputDevice* GetInputDevice();

	//���캯��
	PollEvent();
	//����
	~PollEvent();

	//��������豸����
	void AddInputDevice(BasicInputDevice* inputDevice);

	//����¼��ص�����
	void SetEventCallback(int eventcode, std::function<void()> fun);

	//������Ϣ
	void Update();
};

/// <summary>
/// ��ȡ������ָ�����͵������豸����
/// </summary>
/// <typeparam name="T">����Ŀ����������������</typeparam>
/// <returns></returns>
template<class T>
inline BasicInputDevice* PollEvent::GetInputDevice()
{
	for (auto it = inputDevices.begin(); it != inputDevices.end(); it++)
	{
		if (typeid(T).name == (*it)->GetClassInfo().name())
		{
			return dynamic_cast<T*> (*it);  //����ת������
		}
	}
	return nullptr;
}
