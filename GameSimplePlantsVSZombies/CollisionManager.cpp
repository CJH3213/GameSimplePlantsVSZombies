#include "CollisionManager.h"
#include "GameObject.h"

void CollisionManager::InsertIntoNode(ICollider* collider)
{
	//��ײ�����⣬����������Ĳ�����������
	mRootNode->AddCollider(collider);
}

CollisionManager::CollisionManager(class Game* game, const Vector2& center, const Vector2& size) :
	mGame(game)
{
	mRootNode = new CollisionQuadTree(mGame, center, size);
}

CollisionManager::~CollisionManager()
{
	delete mRootNode;
}


void CollisionManager::AddCollider(ICollider* collider)
{
	auto it = std::find(mColliders.begin(), mColliders.end(), collider);
	if(it == mColliders.end())
	{
		mColliders.emplace_back(collider);
		InsertIntoNode(collider);
	}
}

void CollisionManager::RemoveCollider(ICollider* collider)
{

	// ��������������������ײ��
	auto it = find(mColliders.begin(), mColliders.end(), collider);
	if(it != mColliders.end())
	{
		mColliders.erase(it);
		// ���Ĳ�������������ײ��
		bool res = mRootNode->RemoveCollider(collider);
	}
}

void CollisionManager::AddPointer(IPointer* collider)
{
	mPointers.emplace_back(collider);
}

void CollisionManager::RemovePointer(IPointer* collider)
{
	auto it = find(mPointers.begin(), mPointers.end(), collider);
	if (it != mPointers.end())
		mPointers.erase(it);
}

void CollisionManager::DetectionAll()
{
	for (auto it = mColliders.begin(); it != mColliders.end(); it++)
	{
		if((*it)->IsColliderEnable() == true)
		{
			mRootNode->DetectionWith(*it);
			(*it)->LateCollideUpdate();
		}
	}
}

void CollisionManager::DetectionWithMouse()
{
	// ��ȡ�������
	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector2 mousePos(x, y);
	// ����������ײ�������������ཻ
	for (auto& collider : mPointers)
	{
		if (collider->IsIntersectWithPoint(mousePos))
			collider->OnMouseCallback(mousePos);
		collider->LateMouseUpdate(mousePos);
	}
}

void CollisionManager::OnGameLoop()
{
	// ά���Ĳ���
	mRootNode->MaintainTree();
	// ��������ײ���
	DetectionAll();
	// ���������ײ���
	DetectionWithMouse();
}

