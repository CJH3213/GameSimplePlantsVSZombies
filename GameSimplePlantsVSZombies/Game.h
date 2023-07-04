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
	// ��Ϸ�Ƿ��ܼ�����־
	bool mIsRunning = false;

public:
	// �������
	Window* mWindow = nullptr;
	// ͼƬ��Դ������
	ImageManagement* mImageManagement = nullptr;
	// �ֿ���Դ������
	FontManager* mFontManager = nullptr;
	//��Ϣ��
	PollEvent* mPollEvent = nullptr;
	// ��ײ������
	CollisionManager* mCollisionManager = nullptr;
	// ����������
	SceneManager* mSceneManager = nullptr;
	// ��Ⱦ������
	RenderManager* mRenderManager = nullptr;

	// ���캯��
	Game(std::string name);

	// ��Ϸ��ʼ����ʼ��SDL���������塢������Դ
	void Start();
	// ����
	void Main();
	// ��Ϸ�������ر�ǰ�Ĵ������������ݡ����桢��������
	void Finish();

	// �ر���Ϸ
	void QuitGame();
	// ����״̬�仯�¼��ص�
	void WindowEventCallback();
	// ��Ⱦ�������¼��ص�
	void RenderEventCallback();
};

