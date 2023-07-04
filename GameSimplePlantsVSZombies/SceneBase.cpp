#include "SceneBase.h"

SceneBase::SceneBase(std::string name) :
	mName(name)
{
}

SceneBase::~SceneBase()
{
	// ������Ծ��������
	for (auto obj : mGameObjects)
		delete obj;
	// ���������������
	for (auto obj : mPendingGameObjects)
		delete obj;
}

void SceneBase::AddGameObject(GameObject* gObj)
{
	gObj->SetScene(this);
	mPendingGameObjects.emplace_back(gObj);
}

void SceneBase::AddGameObject(Prefab* gObj)
{
	gObj->SetScene(this);
	gObj->Instantiate();
	mPendingGameObjects.emplace_back(gObj);
}

void SceneBase::RemoveGameObject(GameObject* obj)
{
	auto iter = find(mPendingGameObjects.begin(), mPendingGameObjects.end(), obj);
	if (iter != mPendingGameObjects.end())
	{
		//�����Ȳ���Ч�ʸ�
		std::iter_swap(iter, mPendingGameObjects.end() - 1);
		mPendingGameObjects.pop_back();
	}

	iter = find(mGameObjects.begin(), mGameObjects.end(), obj);
	if (iter != mGameObjects.end())
	{
		//�����Ȳ���Ч�ʸ�
		std::iter_swap(iter, mGameObjects.end() - 1);
		mGameObjects.pop_back();
	}
}

GameObject* SceneBase::FindGameObject(std::string name)
{
	for (auto& obj : mGameObjects)
	{
		if (obj->GetName() == name)
			return obj;
	}

	for (auto& obj : mPendingGameObjects)
	{
		if (obj->GetName() == name)
			return obj;
	}

	return nullptr;
}

void SceneBase::Paused()
{
	for (auto& obj : mGameObjects)
		obj->mState = GameObject::EPaused;
}


