#pragma once
#include "Window.h"
#include "IRenderer.h"
#include <vector>

class RenderManager
{
private:

	// 渲染组件集合
	std::vector<IRenderer*> mRenders;

public:
	//class Game* mGame;
	// 渲染目标窗体对象
	Window* mWindow = nullptr;

	// 构造函数
	RenderManager(Window* window);
	// 析构函数
	~RenderManager();

	// 在游戏循环执行
	void OnGameLoop();

	// 添加渲染组件
	void AddComponent(IRenderer* comp);
	// 移除渲染组件
	void RemoveComponent(IRenderer* comp);
	// 改变组件层级
	void ChangeDrawOrder(IRenderer* comp);
};

