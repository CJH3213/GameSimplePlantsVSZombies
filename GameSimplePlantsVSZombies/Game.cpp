#include "Game.h"
#include "LoadingPageScene.h"
#include "AdventurePage.h"
#include "AudioDevice.h"
#include "WAV_File.h"

Game::Game(std::string name)
{
}

/// <summary>
/// 游戏开始：初始化SDL、创建窗体、加载资源
/// </summary>
void Game::Start()
{
	mIsRunning = true;

	/*------------------系统支持初始化------------------*/
	// 创建窗口
	mWindow = new Window(u8"简易版植物大战僵尸", 800, 600);
	// 图标加载需要依赖图片库（貌似没有初始化IMG也能正常加载图标？）
	mWindow->SetIcon("Resource/Images/bullet1.jpg");

	// 音频设备开启（SDL只能操作单个音频设备，所以是单例模式）
	AudioDevice::Open();

	/*------------------资源管理器初始化------------------*/
	// 创建图片管理器
	mImageManagement = new ImageManagement(mWindow->GetSDLRenderer(), "Resource/Images/");
	// 创建字体管理器
	mFontManager = new FontManager(mWindow->GetSDLRenderer(), "Resource/Fonts/");

	/*------------------游戏系统初始化------------------*/
	// 渲染管理器实例化
	mRenderManager = new RenderManager(mWindow);
	// 碰撞管理器
	mCollisionManager = new CollisionManager(this, {500, 300}, {400, 400});
	//场景管理器实例化
	mSceneManager = new SceneManager(this);

	// 实例消息泵对象
	mPollEvent = new PollEvent();
	// 添加鼠标和键盘设备
	//pollEvent->AddInputDevice(new MouseState());
	//pollEvent->AddInputDevice(new KeyboardState());
	// 添加回调事件（没封装好）
	mPollEvent->SetEventCallback(SDL_QUIT, std::bind(&Game::QuitGame, this));	//关闭窗口退出游戏
	mPollEvent->SetEventCallback(SDL_WINDOWEVENT, std::bind(&Game::WindowEventCallback, this));	//窗口事件回调
	mPollEvent->SetEventCallback(SDL_RENDER_TARGETS_RESET, std::bind(&Game::RenderEventCallback, this));	//渲染器事件回调

	/*------------------以上为底层级初始化，以下为应用级初始化------------------*/

	//加载第一个场景
	SceneBase* page1 = new LoadingPageScene("LoadingPageScene");
	//SceneBase* page1 = new AdventurePage("AdventurePage");
	mSceneManager->LoadScene(page1);

	/*------------------测试代码------------------*/

}

/// <summary>
/// 游戏运行主体（大循环）
/// </summary>
void Game::Main()
{
	while (mIsRunning)
	{
		// 场景预处理
		mSceneManager->OnGameLoop_Pre();
		// 输入更新
		mPollEvent->Update();
		// 碰撞更新
		mCollisionManager->OnGameLoop();
		// 逻辑更新
		mSceneManager->OnGameLoop_Update();
		// 动画更新
		// 渲染更新
		mRenderManager->OnGameLoop();
		// 音频更新（额音频不需要帧更新也不需要管理器）

		//SDL_Log("  ");
	}
}

/// <summary>
/// 游戏结束（关闭前的处理）：整理数据、保存、清理垃圾
/// </summary>
void Game::Finish()
{
	// 销毁消息泵
	delete mPollEvent;
	// 销毁碰撞管理器
	delete mCollisionManager;
	// 销毁渲染管理器
	delete mRenderManager;

	// 销毁场景管理器：销毁所有场景、游戏对象、组件
	delete mSceneManager;

	// 销毁图像资源管理器
	delete mImageManagement;
	// 销毁字库资源管理器
	delete mFontManager;

	// 音频设备关闭
	AudioDevice::Close();
	// 销毁窗口
	delete mWindow;
}

//可能是因为SDL在最小化时暂停了渲染，但仍然保留着大量的GPU资源和内存分配，
//以便在窗口恢复时能够快速绘制图像。这可能会导致GPU满负荷和内存使用量增加。
//当你还原窗口后，SDL会重新分配GPU和内存资源，使其恢复正常。
//为解决此问题可以尝试使用SDL_WM_GrabInput取消最小化时的渲染暂停，
//或通过改变程序中 SDL_GL_SetAttribute 和 SDL_SetVideoMode 函数的参数来减少GPU和内存资源需求。

/// <summary>
/// 退出游戏申请
/// </summary>
void Game::QuitGame()
{
	mIsRunning = false;
}

/// <summary>
/// 窗体事件回调
/// </summary>
void Game::WindowEventCallback()
{
	//窗口最小化事件
	if (SDL_GetWindowFlags(mWindow->GetSDLWindow()) & SDL_WINDOW_MINIMIZED)
	{
	}
}

void Game::RenderEventCallback()
{
	SDL_Log(u8"渲染器出问题了！！%d", mWindow->GetSDLRenderer());
}
