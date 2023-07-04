#pragma once

/// <summary>
/// 用于包装预制件具体类型
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class PrefabPack
{
public:
	// 创建预制件的实例
	T* CreateInstance();
};

template<class T>
inline T* PrefabPack<T>::CreateInstance()
{
	return new T();
}
