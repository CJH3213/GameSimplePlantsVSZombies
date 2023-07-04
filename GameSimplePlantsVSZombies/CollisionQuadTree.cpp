#include "CollisionQuadTree.h"
#include "Game.h"

CollisionQuadTree::CollisionQuadTree(class Game* game, Vector2 center, Vector2 size):
	mGame(game)
{
	for (int i = 0; i < 4; i++)
		mSubNodes[i] = nullptr;

	mBounds.mCenter = center;
	mBounds.mSize = size;

	// ����Ⱦ�����ӵ���Ⱦ������
	mGame->mRenderManager->AddComponent(this);
}

CollisionQuadTree::~CollisionQuadTree()
{
	// �����Ĳ����ӽڵ�
	for (int i = 0; i < 4; i++)
		delete mSubNodes[i];

	// ����ǰ�������Ⱦ����������
	mGame->mRenderManager->RemoveComponent(this);
}

int CollisionQuadTree::GetContainNode(ICollider* collider)
{
	//�ж���ײ���Ƿ��ڵ�ǰ�ڵ㷶Χ��
	if (! collider->GetBounds().IsInside(mBounds))		//�����п��ܿ�ָ�뱨��ע��һ��
	{
		return -2;		//�ڵ�ǰ�ڵ��⣬��Ǹ
	}

	//������Ӧ�ô����ĸ��ӽڵ���
	Rectangle childRect;
	childRect.mSize = mBounds.mSize / 2;
	int index = -1;
	for (int i = 0; i < 4; i++)
	{
		childRect.mCenter = GetChildCenter(i);
		if (collider->GetBounds().IsInside(childRect))
		{
			index = i;		//��¼���԰�Χ������ӽڵ��±�
			break;
		}
	}
	return index;

}

Vector2 CollisionQuadTree::GetChildCenter(uint8_t quad)
{
	//��������ӽڵ㣬ֱ�Ӷ�����������
	if (mSubNodes[quad] != nullptr)
		return mSubNodes[quad]->mBounds.mCenter;

	//�����û�����Ľڵ㣬�����
	Vector2 subSizeHalf = mBounds.mSize / 4;	//�Ӵ�С��һ�룬���ڼ�������ֵ
	Vector2& thisCenter = mBounds.mCenter;
	switch (quad)
	{
	case 0:		//���Ͻڵ�
		return Vector2(thisCenter.x + subSizeHalf.x, thisCenter.y - subSizeHalf.y);
	case 1:		//���Ͻڵ�
		return Vector2(thisCenter.x - subSizeHalf.x, thisCenter.y - subSizeHalf.y);
	case 2:		//���½ڵ�
		return Vector2(thisCenter.x - subSizeHalf.x, thisCenter.y + subSizeHalf.y);
	case 3:		//���½ڵ�
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
	//�����ڵ�ǰ�ڵ��ⲿ���޷����
	if (AddColliderWithoutBigger(collider) == false)
	{
		//��ײ������Ĳ����ĸ���������õ�Ϊ��������
		Vector2 vertex[4];
		vertex[0] = mBounds.GetTopRightPoint();
		vertex[1] = mBounds.GetTopLeftPoint();
		vertex[2] = mBounds.GetBottomLeftPoint();
		vertex[3] = mBounds.GetBottomRightPoint();
		//Ѱ���������
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

		//�����������
		CollisionQuadTree* newTree = new CollisionQuadTree(mGame,
			vertex[index], mBounds.mSize * 2);
		std::swap(*newTree, *this);	//��ǰ������¶��󽻻������ֵ�ǰ����ʼ��Ϊ������
		this->mSubNodes[(index + 2) % 4] = newTree;	//(index+2)%4��ȡ�Խ�����
		//�ݹ�������ĸ��Ĳ���
		AddCollider(collider);
	}
}

bool CollisionQuadTree::AddColliderWithoutBigger(ICollider* collider)
{
	int index = GetContainNode(collider);
	//�����ڵ�ǰ�ڵ��ⲿ���޷����
	if (index == -2)
		return false;

	//�����ڵ��ཻ�������ڵ�ǰ�ڵ�
	else if (index == -1 || GetCollidersCount() < mThreshold)
		mObjects.emplace_back(collider);

	//���ӽڵ��ཻ��������ӽڵ�
	else
	{
		//δ���ӽڵ㣬����������
		if (mSubNodes[index] == nullptr)
		{
			mSubNodes[index] = new CollisionQuadTree(mGame, GetChildCenter(index), mBounds.mSize / 2);
			//����ǰ�ڵ�������������ӵ��ӽڵ�
			for (auto it = mObjects.begin(); it != mObjects.end();)
			{
				if (mSubNodes[index]->AddColliderWithoutBigger(*it))	//��ӳɹ��ľ�ɾ��
					it = mObjects.erase(it);
				else
					it++;
			}
		}
		//�����ӽڵ㣬�����ӽڵ�
		mSubNodes[index]->AddColliderWithoutBigger(collider);
	}

	return true;
}

bool CollisionQuadTree::RemoveCollider(ICollider* collider)
{
	//��ǰ�ڵ������Ƿ��и���ײ��
	auto it = find(mObjects.begin(), mObjects.end(), collider);
	if (it != mObjects.end())
	{
		mObjects.erase(it);

		return true;
	}

	//���ӽڵ�Ѱ����ײ��
	for (int i = 0; i < 4; i++)
	{
		if (mSubNodes[i] != nullptr &&
			mSubNodes[i]->RemoveCollider(collider) == true)
		{
			if (mSubNodes[i]->GetCollidersCount() == 0)	//����ӽڵ�û�����ˣ�ɾ���ӽڵ�
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
	//������ȱ�����⣬�����Ϊ������ȣ������Ӷ�������

	//��ͬ������ཻ���
	for (auto it = mObjects.begin(); it != mObjects.end(); it++)
	{

		if ((*it) != collider && (*it)->IsColliderEnable() == true &&
			(*it)->GetBounds().IsIntersect(collider->GetBounds()))
		{
			// ����������ײ���Ļص��������в�������һ�ε��������Ļص���
			//(*it)->OnCollisionCallback(collider);
			collider->OnCollisionCallback(*it);
		}
	}
	//���Ӳ�����ཻ���
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
			// ���ж϶����Ƿ��ڵ�ǰ�ڵ㷶Χ��
			if (obj->GetBounds().IsInside(mBounds) == false)
			{
				// ���´Ӹ��ڵ����
				it = mObjects.erase(it);
				tempObjs.emplace_back(obj);	// ��¼�����²������ײ��
				moved = true;
			}
			// ȷ���ڵ�ǰ�ڵ���
			else
			{
				// �Ƿ���Բ����ӽڵ��أ�����ӽڵ����
				for (int i = 0; i < 4; i++)
					if (mSubNodes[i] != nullptr &&
						obj->GetBounds().IsInside(mSubNodes[i]->mBounds))
					{
						// ���뵽�ӽڵ���
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

	// �ݹ��4���ӽڵ����ά��
	for (int i = 0; i < 4; i++)
		if (mSubNodes[i] != nullptr)
		{
			mSubNodes[i]->MaintainTree(root);
			//����ӽڵ�û�����ˣ�ɾ���ӽڵ�
			if (mSubNodes[i] != nullptr &&
				mSubNodes[i]->GetCollidersCount() == 0)	
			{
				delete mSubNodes[i];
				mSubNodes[i] = nullptr;
			}
		}

	// ���²������ײ��
	for (auto& obj : tempObjs)
	{
		root.AddCollider(obj);
	}
}

void CollisionQuadTree::OnRender(Window* w)
{
	// �����ӿ�ʾ��ͼ
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

	//���Ƶ�ǰ�ڵ��
	w->SetPenColor(255, 255, 165, 0);	//����
	w->DrawRectangle(mBounds);
}
