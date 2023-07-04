#pragma once
#include <vector>
#include "Prefab.h"
#include "SceneBase.h"
#include <unordered_map>

class PrefabManager
{
private:
	// 储存预制件的容器
	std::unordered_map<std::string, Prefab*> mPrefabs;

	// Game对象（游戏上下文）
	class Game* mGame = nullptr;
	// 虚拟场景，用于预制件初始化
	SceneBase mVirtualScene;

public:
	// 构造函数
	PrefabManager(class Game* game);

	// 添加一个预制件到管理器
	template<typename T>
	void AddPrefab();
};

template<typename T>
inline void PrefabManager::AddPrefab()
{
	// 检查是否已经添加过
	std::string className = typeid(T).name();
	if (mPrefabs.count(className) > 0)
		return;

	// 如未添加过，实例化一个预制件作为模板
	Prefab* prefab = new T();
	mPrefabs.emplace(className, prefab);
	prefab->mScene = mVirtualScene;

	// 调用Instantiate初始化生成子对象和组件
	prefab->Instantiate();

	// 由于该对象添加进虚拟场景，没有受到主场景管理器的遍历
	// 所以该对象的生命周期并不会运行
}
