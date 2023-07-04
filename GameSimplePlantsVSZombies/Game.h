#pragma once

#include "Window.h"
#include "ImageManagement.h"
#include "FontManager.h"
#include "PollEvent.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "RenderManager.h"

class Game
{
private:
	// 游戏是否能继续标志
	bool mIsRunning = false;

public:
	// 窗体对象
	Window* mWindow = nullptr;
	// 图片资源管理器
	ImageManagement* mImageManagement = nullptr;
	// 字库资源管理器
	FontManager* mFontManager = nullptr;
	//消息泵
	PollEvent* mPollEvent = nullptr;
	// 碰撞管理器
	CollisionManager* mCollisionManager = nullptr;
	// 场景管理器
	SceneManager* mSceneManager = nullptr;
	// 渲染管理器
	RenderManager* mRenderManager = nullptr;

	// 构造函数
	Game(std::string name);

	// 游戏开始：初始化SDL、创建窗体、加载资源
	void Start();
	// 主体
	void Main();
	// 游戏结束（关闭前的处理）：整理数据、保存、清理垃圾
	void Finish();

	// 关闭游戏
	void QuitGame();
	// 窗口状态变化事件回调
	void WindowEventCallback();
	// 渲染器重置事件回调
	void RenderEventCallback();
};

