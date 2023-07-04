#pragma once

/// <summary>
/// ���ڰ�װԤ�Ƽ���������
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class PrefabPack
{
public:
	// ����Ԥ�Ƽ���ʵ��
	T* CreateInstance();
};

template<class T>
inline T* PrefabPack<T>::CreateInstance()
{
	return new T();
}
