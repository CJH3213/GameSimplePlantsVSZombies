#include "ComponentBase.h"
#include "SceneBase.h"
#include "Game.h"
#include "GameObject.h"
#include "TransformComponent.h"

ComponentBase::ComponentBase()
{
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::SetOwner(GameObject* obj)
{
	mGameObject = obj;
}

void ComponentBase::SetEnable(bool b)
{
	// ʹ��״̬�ı�ʱ�ص���Ӧ����
	if(mIsEnable != b)
	{
		mIsEnable = b;
		if (mIsEnable) OnEnable();
		else OnDisable();
	}
}

void ComponentBase::_Update()
{
	//��һ��ִ��Updateǰ����һ��Start
	if (mIsStarted == false)
	{
		mIsStarted = true;
		Start();
	}

	Update();
}

Game* ComponentBase::GetGame()
{
	return GetScene()->GetGame();
}

SceneBase* ComponentBase::GetScene()
{
	return mGameObject->GetScene();
}

TransformComponent* ComponentBase::GetTransform()
{
	return mGameObject->mTransform;
}

void ComponentBase::Destroy(GameObject* gObj)
{
	// ��ǽ�ɫ�������������Զ����ٽ�ɫ
	if(gObj != nullptr)
		gObj->mState = GameObject::EDead;
}

void ComponentBase::DestroyAllChildren(GameObject* gObj)
{
	if(gObj != nullptr)
	{
		auto trans = gObj->mTransform;
		for (int i = trans->ChildCount() - 1; i >= 0; i--)
		{
			auto child = trans->GetChild(i);
			DestroyAllChildren(child->GetGameObject());	//�ݹ�����
			Destroy(child->mGameObject);
		}
	}
}
