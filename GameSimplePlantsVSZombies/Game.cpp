#include "Game.h"
#include "LoadingPageScene.h"
#include "AdventurePage.h"
#include "AudioDevice.h"
#include "WAV_File.h"

Game::Game(std::string name)
{
}

/// <summary>
/// ��Ϸ��ʼ����ʼ��SDL���������塢������Դ
/// </summary>
void Game::Start()
{
	mIsRunning = true;

	/*------------------ϵͳ֧�ֳ�ʼ��------------------*/
	// ��������
	mWindow = new Window(u8"���װ�ֲ���ս��ʬ", 800, 600);
	// ͼ�������Ҫ����ͼƬ�⣨ò��û�г�ʼ��IMGҲ����������ͼ�ꣿ��
	mWindow->SetIcon("Resource/Images/bullet1.jpg");

	// ��Ƶ�豸������SDLֻ�ܲ���������Ƶ�豸�������ǵ���ģʽ��
	AudioDevice::Open();

	/*------------------��Դ��������ʼ��------------------*/
	// ����ͼƬ������
	mImageManagement = new ImageManagement(mWindow->GetSDLRenderer(), "Resource/Images/");
	// �������������
	mFontManager = new FontManager(mWindow->GetSDLRenderer(), "Resource/Fonts/");

	/*------------------��Ϸϵͳ��ʼ��------------------*/
	// ��Ⱦ������ʵ����
	mRenderManager = new RenderManager(mWindow);
	// ��ײ������
	mCollisionManager = new CollisionManager(this, {500, 300}, {400, 400});
	//����������ʵ����
	mSceneManager = new SceneManager(this);

	// ʵ����Ϣ�ö���
	mPollEvent = new PollEvent();
	// ������ͼ����豸
	//pollEvent->AddInputDevice(new MouseState());
	//pollEvent->AddInputDevice(new KeyboardState());
	// ��ӻص��¼���û��װ�ã�
	mPollEvent->SetEventCallback(SDL_QUIT, std::bind(&Game::QuitGame, this));	//�رմ����˳���Ϸ
	mPollEvent->SetEventCallback(SDL_WINDOWEVENT, std::bind(&Game::WindowEventCallback, this));	//�����¼��ص�
	mPollEvent->SetEventCallback(SDL_RENDER_TARGETS_RESET, std::bind(&Game::RenderEventCallback, this));	//��Ⱦ���¼��ص�

	/*------------------����Ϊ�ײ㼶��ʼ��������ΪӦ�ü���ʼ��------------------*/

	//���ص�һ������
	SceneBase* page1 = new LoadingPageScene("LoadingPageScene");
	//SceneBase* page1 = new AdventurePage("AdventurePage");
	mSceneManager->LoadScene(page1);

	/*------------------���Դ���------------------*/

}

/// <summary>
/// ��Ϸ�������壨��ѭ����
/// </summary>
void Game::Main()
{
	while (mIsRunning)
	{
		// ����Ԥ����
		mSceneManager->OnGameLoop_Pre();
		// �������
		mPollEvent->Update();
		// ��ײ����
		mCollisionManager->OnGameLoop();
		// �߼�����
		mSceneManager->OnGameLoop_Update();
		// ��������
		// ��Ⱦ����
		mRenderManager->OnGameLoop();
		// ��Ƶ���£�����Ƶ����Ҫ֡����Ҳ����Ҫ��������

		//SDL_Log("  ");
	}
}

/// <summary>
/// ��Ϸ�������ر�ǰ�Ĵ������������ݡ����桢��������
/// </summary>
void Game::Finish()
{
	// ������Ϣ��
	delete mPollEvent;
	// ������ײ������
	delete mCollisionManager;
	// ������Ⱦ������
	delete mRenderManager;

	// ���ٳ������������������г�������Ϸ�������
	delete mSceneManager;

	// ����ͼ����Դ������
	delete mImageManagement;
	// �����ֿ���Դ������
	delete mFontManager;

	// ��Ƶ�豸�ر�
	AudioDevice::Close();
	// ���ٴ���
	delete mWindow;
}

//��������ΪSDL����С��ʱ��ͣ����Ⱦ������Ȼ�����Ŵ�����GPU��Դ���ڴ���䣬
//�Ա��ڴ��ڻָ�ʱ�ܹ����ٻ���ͼ������ܻᵼ��GPU�����ɺ��ڴ�ʹ�������ӡ�
//���㻹ԭ���ں�SDL�����·���GPU���ڴ���Դ��ʹ��ָ�������
//Ϊ�����������Գ���ʹ��SDL_WM_GrabInputȡ����С��ʱ����Ⱦ��ͣ��
//��ͨ���ı������ SDL_GL_SetAttribute �� SDL_SetVideoMode �����Ĳ���������GPU���ڴ���Դ����

/// <summary>
/// �˳���Ϸ����
/// </summary>
void Game::QuitGame()
{
	mIsRunning = false;
}

/// <summary>
/// �����¼��ص�
/// </summary>
void Game::WindowEventCallback()
{
	//������С���¼�
	if (SDL_GetWindowFlags(mWindow->GetSDLWindow()) & SDL_WINDOW_MINIMIZED)
	{
	}
}

void Game::RenderEventCallback()
{
	SDL_Log(u8"��Ⱦ���������ˣ���%d", mWindow->GetSDLRenderer());
}
