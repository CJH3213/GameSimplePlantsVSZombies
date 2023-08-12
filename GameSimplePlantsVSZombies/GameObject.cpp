#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneBase.h"

GameObject::GameObject(std::string name, std::string tag)
	:mName(name), mTag(tag)
{
	mState = EPaused;	//��Ϸ����״̬�ȳ�ʼΪ��̬ͣ

	//��ӱ任���
	mTransform = new TransformComponent();
	AddComponent(mTransform);
}

GameObject::GameObject(std::string name)
	: GameObject(name, "Untagged")
{
}

GameObject::~GameObject()
{
	//���������������������
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
	// �ȴӻ�Ծ�������Ѱ��
	auto it = std::find(mComponents.begin(), mComponents.end(), comp);
	if (it != mComponents.end())
	{
		mComponents.erase(it);
		delete comp;
	}
	else
	{
		// �ٵ������������Ѱ��
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
//	// �ȴӻ�Ծ�������Ѱ��
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
//	// �ٵ������������Ѱ��
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
	// �㼶��ϵӦ�ɱ任�������
	mTransform->SetParent(obj->mTransform);
	// ��Ծ�Ը��游����
	SetActive(obj->GetActive());
}

GameObject::GameObject(const GameObject& other)
{
	this->mName = other.mName + "_Copy";
	this->mTag = other.mTag;
	mScene = other.mScene;

	// �������нű�
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

	// ��ȡ�任�������
	mTransform = GetComponent<TransformComponent>();
}

void GameObject::SetActive(bool b)
{
	if (mIsActive != b)
	{
		mIsActive = b;

		// ���õ�ǰ�����������
		for (auto comp : mComponents)
			comp->SetEnable(b);
		// ��������п��ܻ�������⣬�Ժ�������˵
		for (auto comp : mPendingComponents)
			comp->SetEnable(b);

		// ���������Ӷ���
		for (int i = 0; i < mTransform->ChildCount(); i++)
		{
			mTransform->GetChild(i)->GetGameObject()->SetActive(b);
		}
	}

}

void GameObject::PreUpdate()
{
	// ִ��������������Awake����ת������
	for (auto& comp : mPendingComponents)
	{
		comp->Awake();
		mComponents.emplace_back(comp);
	}
	// ��
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

