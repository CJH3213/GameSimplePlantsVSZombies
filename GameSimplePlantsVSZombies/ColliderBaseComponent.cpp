#include "ColliderBaseComponent.h"
#include "GameObject.h"
#include "Game.h"

ColliderBaseComponent::ColliderBaseComponent(std::string name):
	ComponentBase(name)
{
}

ColliderBaseComponent::~ColliderBaseComponent()
{
	// ����ʱ���������ײ����������
	GetGame()->mCollisionManager->RemoveCollider(this);
	// 
	GetGame()->mRenderManager->RemoveComponent(this);
}

void ColliderBaseComponent::Awake()
{
	// �����������Ϸ���������Զ����������ϵͳ
	GetGame()->mCollisionManager->AddCollider(this);
	// ����Ⱦ����������Ⱦϵͳ
	GetGame()->mRenderManager->AddComponent(this);
}

void ColliderBaseComponent::OnCollisionCallback(ICollider* other)
{
	// ��������ײ״̬�����¼��
	auto iter = mRecords.find(other);
	if (iter == mRecords.end())
	{
		CollisionInfo state = { false, false };
		mRecords.insert({ other, state });
	}
	(*iter).second.mCurrState = true;
}

GameObject* ColliderBaseComponent::GetGameObj()
{
	return mGameObject;
}

Rectangle& ColliderBaseComponent::GetBounds()
{
	return mBounds;
}

bool ColliderBaseComponent::IsIntersectWithAABB(Rectangle& r)
{
	return mBounds.IsIntersect(r);
}

void ColliderBaseComponent::LateCollideUpdate()
{
	// ������ײ���Ϊfalse�ļ�¼����Ϊ�����Ѿ�������ײ
	for (auto iter = mRecords.begin(); iter != mRecords.end();)
	{
		auto& state = (*iter).second;
		if (state.mPrevState == false)
		{
			if (state.mCurrState == false)
			{
				mRecords.erase(iter);
				continue;
			}
			else  //�����أ���ײ��һ֡
				OnCollisionEnter((*iter).first);
		}
		else
		{
			// �ߵ�ƽ��������ײ
			if (state.mCurrState == false)
				OnCollisionStay((*iter).first);
			else //�½��أ���ײ���һ֡
			{
				OnCollisionExit((*iter).first);
				mRecords.erase(iter);
				continue;
			}
		}
		// ������¼ֵ��Ϊ�´���ײ���׼��
		state.mPrevState = state.mCurrState;
		state.mCurrState = false;
		// ��������һλ
		iter++;
	}

}

//void ColliderBaseComponent::OnMouseCallback(Vector2 pos)
//{
//	// ��¼�����ͣ����ײ����
//	mMouseHover.mCurrState = true;
//	// ��¼�������ײ����ֻҪ�������
//	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))
//		mMouseClick.mCurrState = true;
//}
//
//void ColliderBaseComponent::LateMouseUpdate(Vector2 pos)
//{
//	// �����ͣ�¼�
//	if (mMouseHover.mPrevState == false)
//	{
//		if (mMouseHover.mCurrState == true)
//			OnMouseEnter(pos);	//��һ֡������
//	}
//	else
//	{
//		if (mMouseHover.mCurrState == true)
//			OnMouseOver(pos);		//��������ͣ
//		else
//			OnMouseExit(pos);		//����뿪
//	}
//	// �����μ�¼ֵ��Ϊ�ϼ�¼��Ϊ�´���׼��
//	mMouseHover.mPrevState = mMouseHover.mCurrState;
//	mMouseHover.mCurrState = false;
//
//	// ������¼�
//	if (mMouseClick.mPrevState == false)
//	{
//		if (mMouseClick.mCurrState == true)
//			OnMouseDown(pos);	//��һ֡����������
//	}
//	else
//	{
//		// ��¼�������ײ����ֻҪ�������
//		if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))
//			mMouseClick.mCurrState = true;
//
//		if (mMouseClick.mCurrState == true)
//			OnMouseDrag(pos);		//��������������
//		else
//		{
//			OnMouseUp(pos);		//�������ͷ�
//			// �������ɿ�ʱ����Ȼ��ͣ����ײ���ϣ����ö�Ӧ�ص�
//			if (mMouseHover.mPrevState)
//				OnMouseUpAsButton(pos);
//		}
//	}
//	// �����μ�¼ֵ��Ϊ�ϼ�¼��Ϊ�´���׼��
//	mMouseClick.mPrevState = mMouseClick.mCurrState;
//	mMouseClick.mCurrState = false;
//}

void ColliderBaseComponent::OnRender(Window* w)
{
	w->SetPenColor(255, 255, 0, 0);
	w->DrawRectangle(mBounds);
}

//bool ColliderBaseComponent::CheckWithPoint(const Vector2& point)
//{
//		//�㷨�������������ĵ����ľ���ֵ <= ������һ��
//	Vector2 centerDistance = (mBounds.mCenter - point).AbsThis();
//	Vector2 halfBoxSize = mBounds.mSize / 2;
//
//	return centerDistance.x <= halfBoxSize.x &&
//		centerDistance.y <= halfBoxSize.y;
//}

//bool CheckPointWithPoint(Vector2& point1, Vector2& point2)
//{
//	//�㷨��ֱ���ж�����λ���Ƿ���ͬ
//	return (point1 == point2);
//}

//#include "CircleColliderComponent.h"
//
//bool CheckCircleWithCircle(CircleColliderComponent* circle1, CircleColliderComponent* circle2)
//{
//	//�㷨��d^2 = x^2 + y^2 <= (r1 + r2)^2
//	float centerDistance = (circle1->mBounds.mCenter - circle2->mBounds.mCenter).LengthUNSquared();
//	float limitDistance = (circle1->radius + circle2->radius);
//	return centerDistance <= limitDistance * limitDistance;
//}
//
//bool CheckCircleWithPoint(CircleColliderComponent* circle, Vector2& point)
//{
//	//�㷨��Բ���������� <= Բ�뾶
//	float distance = (circle->mBounds.mCenter - point).LengthUNSquared();
//	return distance <= circle->radius * circle->radius;
//}
//
////#include "BoxColliderComponent.h"
//
//bool CheckBoxWithBox(BoxColliderComponent* box1, BoxColliderComponent* box2)
//{
//	//�㷨�����������Ŀ�� <= �����ο�ߵĺ�
//	Vector2 centerDistance = box1->mBounds.mCenter - box2->mBounds.mCenter;
//	Vector2 limitSize = box1->size - box2->size;
//
//	return centerDistance.x <= limitSize.x && centerDistance.y <= limitSize.y;
//}
//
//bool CheckBoxWithPoint(BoxColliderComponent* box, Vector2& point)
//{
//	//�㷨�������������ĵ����ľ���ֵ <= ������һ��
//	Vector2 centerDistance = (box->mBounds.mCenter - point).AbsThis();
//	Vector2 halfBoxSize = box->size / 2;
//
//	return centerDistance.x <= halfBoxSize.x &&
//		centerDistance.y <= halfBoxSize.y;
//}
//
//bool CheckBoxWithCircle(BoxColliderComponent* box, CircleColliderComponent* circle)
//{
//	//�������Ͻǡ����½�����
//	Vector2 topLeft = box->mBounds.mCenter - box->size / 2;
//	Vector2 bottomRight = box->mBounds.mCenter + box->size / 2;
//
//	//�㷨1�����ζ�����Բ�ڣ���Բ�������Ǿ���С��Բ�뾶
//	Vector2 minV;		//��Բ�ľ�������Ľǣ��Ǻ�Բ�ĵľ���
//	minV.x = fminf(fabsf(topLeft.x - circle->mBounds.mCenter.x), fabsf(bottomRight.x - circle->mBounds.mCenter.x));
//	minV.y = fminf(fabsf(topLeft.y - circle->mBounds.mCenter.y), fabsf(bottomRight.y - circle->mBounds.mCenter.y));
//	if (minV.LengthUNSquared() < (circle->radius * circle->radius))
//		return true;
//
//	//�㷨2��Բ����α��ཻ
//	Vector2 halfBoxSize = box->size / 2;
//	if (fabsf(box->mBounds.mCenter.y - circle->mBounds.mCenter.y) < halfBoxSize.y + circle->radius
//		&& fabsf(box->mBounds.mCenter.x - circle->mBounds.mCenter.x) < halfBoxSize.x)
//		return true;
//	if (fabsf(box->mBounds.mCenter.x - circle->mBounds.mCenter.x) < halfBoxSize.x + circle->radius
//		&& fabsf(box->mBounds.mCenter.y - circle->mBounds.mCenter.y) < halfBoxSize.y)
//		return true;
//
//	return false;
//}

