#pragma once
#include "Window.h"
#include "IRenderer.h"
#include <vector>

class RenderManager
{
private:

	// ��Ⱦ�������
	std::vector<IRenderer*> mRenders;

public:
	//class Game* mGame;
	// ��ȾĿ�괰�����
	Window* mWindow = nullptr;

	// ���캯��
	RenderManager(Window* window);
	// ��������
	~RenderManager();

	// ����Ϸѭ��ִ��
	void OnGameLoop();

	// �����Ⱦ���
	void AddComponent(IRenderer* comp);
	// �Ƴ���Ⱦ���
	void RemoveComponent(IRenderer* comp);
	// �ı�����㼶
	void ChangeDrawOrder(IRenderer* comp);
};

