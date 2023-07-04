#include "CollisionManager.h"
#include "GameObject.h"

void CollisionManager::InsertIntoNode(ICollider* collider)
{
	//碰撞器在外，创建更大的四叉树以容纳它
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

	// 从线性容器中消除该碰撞器
	auto it = find(mColliders.begin(), mColliders.end(), collider);
	if(it != mColliders.end())
	{
		mColliders.erase(it);
		// 从四叉树中消除该碰撞器
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
	// 获取鼠标坐标
	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector2 mousePos(x, y);
	// 遍历所有碰撞器检测与鼠标点的相交
	for (auto& collider : mPointers)
	{
		if (collider->IsIntersectWithPoint(mousePos))
			collider->OnMouseCallback(mousePos);
		collider->LateMouseUpdate(mousePos);
	}
}

void CollisionManager::OnGameLoop()
{
	// 维护四叉树
	mRootNode->MaintainTree();
	// 物与物碰撞检测
	DetectionAll();
	// 物与鼠标碰撞检测
	DetectionWithMouse();
}

