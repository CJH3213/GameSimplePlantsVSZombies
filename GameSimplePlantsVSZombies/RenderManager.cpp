#include "RenderManager.h"

RenderManager::RenderManager(Window* window)
{
	mWindow = window;
}

RenderManager::~RenderManager()
{
}

void RenderManager::OnGameLoop()
{
	// ��С������ʱֹͣ��Ⱦ����ֹ�ڴ��GPU����
	if (mWindow->IsMinimized() == false)
	{
		// ��ջ�����
		mWindow->ClearByColor(255, 0, 255, 0);
		// ����������Ⱦ���
		for (auto it = mRenders.rbegin(); it!= mRenders.rend(); it++)
		{
			if((*it)->IsRenderEnable() == true)
				(*it)->OnRender(mWindow);
		}
		// ���������ύ������
		mWindow->Present();
	}
}

void RenderManager::AddComponent(IRenderer* comp)
{
	int drawOrder = comp->GetDrawOrder();

	auto iter = mRenders.begin();
	// Ѱ�һ��Ʋ㼶�Դ�ĵ�һ�����󣬲�����ǰ��
	for (; iter != mRenders.end(); iter++)
		if (drawOrder <= (*iter)->GetDrawOrder())
			break;

	mRenders.insert(iter, comp);
}

void RenderManager::RemoveComponent(IRenderer* comp)
{
	auto it = std::find(mRenders.begin(), mRenders.end(), comp);
	if (it != mRenders.end())
		mRenders.erase(it);
}

void RenderManager::ChangeDrawOrder(IRenderer* comp)
{
	auto it = std::find(mRenders.begin(), mRenders.end(), comp);
	if (it != mRenders.end())
	{
		mRenders.erase(it);
		// �ҵ�����λ�ã��޳��������²��뼴���������
		AddComponent(comp);
	}
}
