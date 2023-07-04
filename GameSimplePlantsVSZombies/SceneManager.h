#pragma once
#include <vector>
#include "SceneBase.h"

class SceneManager
{
private:
	// 场景容器
	std::vector<SceneBase*> mScenes;
	// 挂起场景容器（其实根本没用上容器）
	std::vector<SceneBase*> mPendingScenes;
	// 当前场景、活跃场景
	SceneBase* mActivityScene = nullptr;
	// Game对象（游戏上下文）
	class Game* mGame = nullptr;

public:
	// 构造函数
	SceneManager(class Game* game) : mGame(game){}

	// 添加场景
	void LoadScene(SceneBase* scene);
	// 添加场景异步
	//void LoadSceneAsync(SceneBase* scene){}
	// 销毁场景
	void DestroyScene(SceneBase* scene){}
	// 获取当前活跃场景
	SceneBase* GetActivityScene();
	//获取第几个场景
	SceneBase* GetSceneAt(int index);
	//通过名称获取场景
	SceneBase* GetSceneByName(std::string name);

	//游戏大循环
	void OnGameLoop_Pre();
	void OnGameLoop_Update();
};

