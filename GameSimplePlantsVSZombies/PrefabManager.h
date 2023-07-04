#pragma once
#include <vector>
#include "Prefab.h"
#include "SceneBase.h"
#include <unordered_map>

class PrefabManager
{
private:
	// ����Ԥ�Ƽ�������
	std::unordered_map<std::string, Prefab*> mPrefabs;

	// Game������Ϸ�����ģ�
	class Game* mGame = nullptr;
	// ���ⳡ��������Ԥ�Ƽ���ʼ��
	SceneBase mVirtualScene;

public:
	// ���캯��
	PrefabManager(class Game* game);

	// ���һ��Ԥ�Ƽ���������
	template<typename T>
	void AddPrefab();
};

template<typename T>
inline void PrefabManager::AddPrefab()
{
	// ����Ƿ��Ѿ���ӹ�
	std::string className = typeid(T).name();
	if (mPrefabs.count(className) > 0)
		return;

	// ��δ��ӹ���ʵ����һ��Ԥ�Ƽ���Ϊģ��
	Prefab* prefab = new T();
	mPrefabs.emplace(className, prefab);
	prefab->mScene = mVirtualScene;

	// ����Instantiate��ʼ�������Ӷ�������
	prefab->Instantiate();

	// ���ڸö�����ӽ����ⳡ����û���ܵ��������������ı���
	// ���Ըö�����������ڲ���������
}
