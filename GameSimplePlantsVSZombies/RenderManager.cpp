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
	// 最小化窗体时停止渲染，防止内存和GPU暴涨
	if (mWindow->IsMinimized() == false)
	{
		// 清空缓存区
		mWindow->ClearByColor(255, 0, 255, 0);
		// 调用所有渲染组件
		for (auto it = mRenders.rbegin(); it!= mRenders.rend(); it++)
		{
			if((*it)->IsRenderEnable() == true)
				(*it)->OnRender(mWindow);
		}
		// 将缓存区提交到窗口
		mWindow->Present();
	}
}

void RenderManager::AddComponent(IRenderer* comp)
{
	int drawOrder = comp->GetDrawOrder();

	auto iter = mRenders.begin();
	// 寻找绘制层级稍大的第一个对象，插入它前面
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
		// 找到插入位置，剔除，再重新插入即可完成排序
		AddComponent(comp);
	}
}
