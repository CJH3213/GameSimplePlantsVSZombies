#include "CollisionQuadTree.h"
#include "Game.h"

CollisionQuadTree::CollisionQuadTree(class Game* game, Vector2 center, Vector2 size):
	mGame(game)
{
	for (int i = 0; i < 4; i++)
		mSubNodes[i] = nullptr;

	mBounds.mCenter = center;
	mBounds.mSize = size;

	// 将渲染组件添加到渲染管理器
	mGame->mRenderManager->AddComponent(this);
}

CollisionQuadTree::~CollisionQuadTree()
{
	// 析构四叉树子节点
	for (int i = 0; i < 4; i++)
		delete mSubNodes[i];

	// 将当前组件与渲染管理器分离
	mGame->mRenderManager->RemoveComponent(this);
}

int CollisionQuadTree::GetContainNode(ICollider* collider)
{
	//判断碰撞器是否在当前节点范围内
	if (! collider->GetBounds().IsInside(mBounds))		//这里有可能空指针报错，注意一下
	{
		return -2;		//在当前节点外，抱歉
	}

	//检测对象应该存在哪个子节点上
	Rectangle childRect;
	childRect.mSize = mBounds.mSize / 2;
	int index = -1;
	for (int i = 0; i < 4; i++)
	{
		childRect.mCenter = GetChildCenter(i);
		if (collider->GetBounds().IsInside(childRect))
		{
			index = i;		//记录可以包围对象的子节点下标
			break;
		}
	}
	return index;

}

Vector2 CollisionQuadTree::GetChildCenter(uint8_t quad)
{
	//如果已有子节点，直接读出中心坐标
	if (mSubNodes[quad] != nullptr)
		return mSubNodes[quad]->mBounds.mCenter;

	//如果还没有中心节点，算出来
	Vector2 subSizeHalf = mBounds.mSize / 4;	//子大小的一半，用于计算中心值
	Vector2& thisCenter = mBounds.mCenter;
	switch (quad)
	{
	case 0:		//右上节点
		return Vector2(thisCenter.x + subSizeHalf.x, thisCenter.y - subSizeHalf.y);
	case 1:		//左上节点
		return Vector2(thisCenter.x - subSizeHalf.x, thisCenter.y - subSizeHalf.y);
	case 2:		//左下节点
		return Vector2(thisCenter.x - subSizeHalf.x, thisCenter.y + subSizeHalf.y);
	case 3:		//右下节点
		return Vector2(thisCenter.x + subSizeHalf.x, thisCenter.y + subSizeHalf.y);
	default:
		return Vector2(0, 0);
	}
}

size_t CollisionQuadTree::GetSubCollidersCount() const
{
	size_t sum = 0;

	for (int i = 0; i < 4; i++)
	{
		if (mSubNodes[i] != nullptr)
		{
			sum += mSubNodes[i]->mObjects.size() + 
				mSubNodes[i]->GetSubCollidersCount();
		}
	}

	return sum;
}

size_t CollisionQuadTree::GetCollidersCount() const
{
	return mObjects.size() + GetSubCollidersCount();
}

void CollisionQuadTree::AddCollider(ICollider* collider)
{
	//对象在当前节点外部，无法添加
	if (AddColliderWithoutBigger(collider) == false)
	{
		//碰撞器离根四叉树哪个顶点近，该点为新树中心
		Vector2 vertex[4];
		vertex[0] = mBounds.GetTopRightPoint();
		vertex[1] = mBounds.GetTopLeftPoint();
		vertex[2] = mBounds.GetBottomLeftPoint();
		vertex[3] = mBounds.GetBottomRightPoint();
		//寻找最近顶点
		float minDistance = (vertex[0] - collider->GetBounds().mCenter).LengthUNSquared();
		uint8_t index = 0;
		for (int i = 1; i < 4; i++)
		{
			float dis = (vertex[i] - collider->GetBounds().mCenter).LengthUNSquared();
			if (dis < minDistance)
			{
				minDistance = dis;
				index = i;
			}
		}

		//创建更大的树
		CollisionQuadTree* newTree = new CollisionQuadTree(mGame,
			vertex[index], mBounds.mSize * 2);
		std::swap(*newTree, *this);	//当前对象和新对象交换，保持当前对象始终为根对象
		this->mSubNodes[(index + 2) % 4] = newTree;	//(index+2)%4获取对角象限
		//递归插入更大的根四叉树
		AddCollider(collider);
	}
}

bool CollisionQuadTree::AddColliderWithoutBigger(ICollider* collider)
{
	int index = GetContainNode(collider);
	//对象在当前节点外部，无法添加
	if (index == -2)
		return false;

	//与多个节点相交，储存于当前节点
	else if (index == -1 || GetCollidersCount() < mThreshold)
		mObjects.emplace_back(collider);

	//与子节点相交，添加入子节点
	else
	{
		//未有子节点，创建，填入
		if (mSubNodes[index] == nullptr)
		{
			mSubNodes[index] = new CollisionQuadTree(mGame, GetChildCenter(index), mBounds.mSize / 2);
			//将当前节点容器对象尝试添加到子节点
			for (auto it = mObjects.begin(); it != mObjects.end();)
			{
				if (mSubNodes[index]->AddColliderWithoutBigger(*it))	//添加成功的就删除
					it = mObjects.erase(it);
				else
					it++;
			}
		}
		//已有子节点，存入子节点
		mSubNodes[index]->AddColliderWithoutBigger(collider);
	}

	return true;
}

bool CollisionQuadTree::RemoveCollider(ICollider* collider)
{
	//当前节点容器是否有该碰撞器
	auto it = find(mObjects.begin(), mObjects.end(), collider);
	if (it != mObjects.end())
	{
		mObjects.erase(it);

		return true;
	}

	//向子节点寻找碰撞器
	for (int i = 0; i < 4; i++)
	{
		if (mSubNodes[i] != nullptr &&
			mSubNodes[i]->RemoveCollider(collider) == true)
		{
			if (mSubNodes[i]->GetCollidersCount() == 0)	//如果子节点没对象了，删除子节点
			{
				delete mSubNodes[i];
				mSubNodes[i] = nullptr;
			}
			return true;
		}
	}

	return false;
}

CollisionQuadTree* CollisionQuadTree::Find(ICollider* collider)
{
	auto it = std::find(mObjects.begin(), mObjects.end(), collider);
	if (it != mObjects.end())
		return this;
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (mSubNodes[i] != nullptr)
			{
				CollisionQuadTree* node = mSubNodes[i]->Find(collider);
				if (node) return node;
			}
		}
	}

	return nullptr;
}

void CollisionQuadTree::DetectionWith(ICollider* collider)
{
	//深度优先遍历检测，如需改为广度优先，需增加队列容器

	//与同层对象相交检测
	for (auto it = mObjects.begin(); it != mObjects.end(); it++)
	{

		if ((*it) != collider && (*it)->IsColliderEnable() == true &&
			(*it)->GetBounds().IsIntersect(collider->GetBounds()))
		{
			// 调用两个碰撞器的回调函数（有病啊干嘛一次调用两个的回调）
			//(*it)->OnCollisionCallback(collider);
			collider->OnCollisionCallback(*it);
		}
	}
	//与子层对象相交检测
	for (int i = 0; i < 4; i++)
	{
		if (mSubNodes[i] != nullptr &&
			mSubNodes[i]->mBounds.IsIntersect(collider->GetBounds()))
			mSubNodes[i]->DetectionWith(collider);
	}
}

void CollisionQuadTree::MaintainTree(CollisionQuadTree& root)
{
	std::vector<ICollider*> tempObjs;

	auto it = mObjects.begin();
	while (it != mObjects.end())
	{
		bool moved = false;

		if((*it)->IsColliderEnable() == true)
		{
			auto obj = (*it);
			// 先判断对象是否还在当前节点范围内
			if (obj->GetBounds().IsInside(mBounds) == false)
			{
				// 重新从根节点插入
				it = mObjects.erase(it);
				tempObjs.emplace_back(obj);	// 记录待重新插入的碰撞器
				moved = true;
			}
			// 确定在当前节点内
			else
			{
				// 是否可以插入子节点呢，如果子节点存在
				for (int i = 0; i < 4; i++)
					if (mSubNodes[i] != nullptr &&
						obj->GetBounds().IsInside(mSubNodes[i]->mBounds))
					{
						// 插入到子节点中
						it = mObjects.erase(it);
						mSubNodes[i]->AddCollider(obj);
						moved = true;
						break;
					}
			}
		}

		if(moved == false)
			it++;
	}

	// 递归对4个子节点进行维护
	for (int i = 0; i < 4; i++)
		if (mSubNodes[i] != nullptr)
		{
			mSubNodes[i]->MaintainTree(root);
			//如果子节点没对象了，删除子节点
			if (mSubNodes[i] != nullptr &&
				mSubNodes[i]->GetCollidersCount() == 0)	
			{
				delete mSubNodes[i];
				mSubNodes[i] = nullptr;
			}
		}

	// 重新插入的碰撞器
	for (auto& obj : tempObjs)
	{
		root.AddCollider(obj);
	}
}

void CollisionQuadTree::OnRender(Window* w)
{
	// 绘制子框示意图
	Rectangle childRect;
	childRect.mSize = mBounds.mSize / 2;

	for (int i = 0; i < 4; i++)
	{
		childRect.mCenter = GetChildCenter(i);

		if (mSubNodes[i])
			w->SetPenColor(255, 255, 165, 0);
		else 
			w->SetPenColor(120, 150, 150, 150);

		w->DrawRectangle(childRect);
	}

	//绘制当前节点框
	w->SetPenColor(255, 255, 165, 0);	//画笔
	w->DrawRectangle(mBounds);
}
