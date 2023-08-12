#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneBase.h"

GameObject::GameObject(std::string name, std::string tag)
	:mName(name), mTag(tag)
{
	mState = EPaused;	//游戏对象状态先初始为暂停态

	//添加变换组件
	mTransform = new TransformComponent();
	AddComponent(mTransform);
}

GameObject::GameObject(std::string name)
	: GameObject(name, "Untagged")
{
}

GameObject::~GameObject()
{
	//析构容器中所有组件对象
	for (auto item : mComponents)
		delete item;
	for (auto item : mPendingComponents)
		delete item;
}

void GameObject::AddComponent(ComponentBase* comp)
{
	mPendingComponents.emplace_back(comp);
	comp->SetOwner(this);
	comp->SetEnable(GetActive());
}

void GameObject::RemoveComponent(ComponentBase* comp)
{
	// 先从活跃组件容器寻找
	auto it = std::find(mComponents.begin(), mComponents.end(), comp);
	if (it != mComponents.end())
	{
		mComponents.erase(it);
		delete comp;
	}
	else
	{
		// 再到挂起组件容器寻找
		it = std::find(mPendingComponents.begin(), mPendingComponents.end(), comp);
		if (it != mPendingComponents.end())
		{
			mPendingComponents.erase(it);
			delete comp;
		}
	}
}

Game* GameObject::GetGame()
{
	return GetScene()->GetGame();
}

//void GameObject::RemoveComponent(std::string name)
//{
//	// 先从活跃组件容器寻找
//	for (auto it = mComponents.begin(); it != mComponents.end(); it++)
//	{
//		if (name == (*it)->GetName())
//		{
//			ComponentBase* comp = (*it);
//			mComponents.erase(it);
//			delete comp;
//			return;
//		}
//	}
//	// 再到挂起组件容器寻找
//	for (auto it = mPendingComponents.begin(); it != mPendingComponents.end(); it++)
//	{
//		if (name == (*it)->GetThisName())
//		{
//			ComponentBase* comp = (*it);
//			mPendingComponents.erase(it);
//			delete comp;
//			return;
//		}
//	}
//}

void GameObject::SetParent(GameObject* obj)
{
	// 层级关系应由变换组件管理
	mTransform->SetParent(obj->mTransform);
	// 活跃性跟随父对象
	SetActive(obj->GetActive());
}

GameObject::GameObject(const GameObject& other)
{
	this->mName = other.mName + "_Copy";
	this->mTag = other.mTag;
	mScene = other.mScene;

	// 拷贝所有脚本
	mComponents.clear();
	mPendingComponents.clear();
	for (auto comp : other.mPendingComponents)
	{
		AddComponent(comp->Clone());
	}
	for (auto comp : other.mComponents)
	{
		AddComponent(comp->Clone());
	}

	// 获取变换组件引用
	mTransform = GetComponent<TransformComponent>();
}

void GameObject::SetActive(bool b)
{
	if (mIsActive != b)
	{
		mIsActive = b;

		// 设置当前对象所有组件
		for (auto comp : mComponents)
			comp->SetEnable(b);
		// 挂起组件有可能会出现问题，以后碰到再说
		for (auto comp : mPendingComponents)
			comp->SetEnable(b);

		// 设置所有子对象
		for (int i = 0; i < mTransform->ChildCount(); i++)
		{
			mTransform->GetChild(i)->GetGameObject()->SetActive(b);
		}
	}

}

void GameObject::PreUpdate()
{
	// 执行所有添加组件的Awake，并转移容器
	for (auto& comp : mPendingComponents)
	{
		comp->Awake();
		mComponents.emplace_back(comp);
	}
	// 清
	mPendingComponents.clear();
}

void GameObject::Update()
{
	for (auto& comp : mComponents)
	{
		if(comp->IsEnable())
			comp->_Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& comp : mComponents)
	{
		if (comp->IsEnable())
			comp->LateUpdate();
	}
}

