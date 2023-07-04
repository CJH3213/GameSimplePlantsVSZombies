#include "ColliderBaseComponent.h"
#include "GameObject.h"
#include "Game.h"

ColliderBaseComponent::ColliderBaseComponent(std::string name):
	ComponentBase(name)
{
}

ColliderBaseComponent::~ColliderBaseComponent()
{
	// 析构时将组件与碰撞管理器分离
	GetGame()->mCollisionManager->RemoveCollider(this);
	// 
	GetGame()->mRenderManager->RemoveComponent(this);
}

void ColliderBaseComponent::Awake()
{
	// 将组件插入游戏对象后，组件自动添加至物理系统
	GetGame()->mCollisionManager->AddCollider(this);
	// 将渲染组件添加至渲染系统
	GetGame()->mRenderManager->AddComponent(this);
}

void ColliderBaseComponent::OnCollisionCallback(ICollider* other)
{
	// 将本次碰撞状态存入记录器
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
	// 本次碰撞结果为false的记录，认为两者已经结束碰撞
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
			else  //上升沿，碰撞第一帧
				OnCollisionEnter((*iter).first);
		}
		else
		{
			// 高电平，持续碰撞
			if (state.mCurrState == false)
				OnCollisionStay((*iter).first);
			else //下降沿，碰撞最后一帧
			{
				OnCollisionExit((*iter).first);
				mRecords.erase(iter);
				continue;
			}
		}
		// 调整记录值，为下次碰撞检测准备
		state.mPrevState = state.mCurrState;
		state.mCurrState = false;
		// 迭代器下一位
		iter++;
	}

}

//void ColliderBaseComponent::OnMouseCallback(Vector2 pos)
//{
//	// 记录鼠标悬停于碰撞器上
//	mMouseHover.mCurrState = true;
//	// 记录鼠标点击碰撞器，只要左键按下
//	if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))
//		mMouseClick.mCurrState = true;
//}
//
//void ColliderBaseComponent::LateMouseUpdate(Vector2 pos)
//{
//	// 鼠标悬停事件
//	if (mMouseHover.mPrevState == false)
//	{
//		if (mMouseHover.mCurrState == true)
//			OnMouseEnter(pos);	//这一帧鼠标进入
//	}
//	else
//	{
//		if (mMouseHover.mCurrState == true)
//			OnMouseOver(pos);		//鼠标持续悬停
//		else
//			OnMouseExit(pos);		//鼠标离开
//	}
//	// 将本次记录值作为老记录，为下次作准备
//	mMouseHover.mPrevState = mMouseHover.mCurrState;
//	mMouseHover.mCurrState = false;
//
//	// 鼠标点击事件
//	if (mMouseClick.mPrevState == false)
//	{
//		if (mMouseClick.mCurrState == true)
//			OnMouseDown(pos);	//这一帧鼠标左键按下
//	}
//	else
//	{
//		// 记录鼠标点击碰撞器，只要左键按下
//		if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT))
//			mMouseClick.mCurrState = true;
//
//		if (mMouseClick.mCurrState == true)
//			OnMouseDrag(pos);		//鼠标左键持续按下
//		else
//		{
//			OnMouseUp(pos);		//鼠标左键释放
//			// 鼠标左键松开时，仍然悬停在碰撞器上，调用对应回调
//			if (mMouseHover.mPrevState)
//				OnMouseUpAsButton(pos);
//		}
//	}
//	// 将本次记录值作为老记录，为下次作准备
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
//		//算法：点与箱体中心点距离的绝对值 <= 箱体宽高一半
//	Vector2 centerDistance = (mBounds.mCenter - point).AbsThis();
//	Vector2 halfBoxSize = mBounds.mSize / 2;
//
//	return centerDistance.x <= halfBoxSize.x &&
//		centerDistance.y <= halfBoxSize.y;
//}

//bool CheckPointWithPoint(Vector2& point1, Vector2& point2)
//{
//	//算法：直接判断两点位置是否相同
//	return (point1 == point2);
//}

//#include "CircleColliderComponent.h"
//
//bool CheckCircleWithCircle(CircleColliderComponent* circle1, CircleColliderComponent* circle2)
//{
//	//算法：d^2 = x^2 + y^2 <= (r1 + r2)^2
//	float centerDistance = (circle1->mBounds.mCenter - circle2->mBounds.mCenter).LengthUNSquared();
//	float limitDistance = (circle1->radius + circle2->radius);
//	return centerDistance <= limitDistance * limitDistance;
//}
//
//bool CheckCircleWithPoint(CircleColliderComponent* circle, Vector2& point)
//{
//	//算法：圆中心与点距离 <= 圆半径
//	float distance = (circle->mBounds.mCenter - point).LengthUNSquared();
//	return distance <= circle->radius * circle->radius;
//}
//
////#include "BoxColliderComponent.h"
//
//bool CheckBoxWithBox(BoxColliderComponent* box1, BoxColliderComponent* box2)
//{
//	//算法：两矩形中心宽高 <= 两矩形宽高的和
//	Vector2 centerDistance = box1->mBounds.mCenter - box2->mBounds.mCenter;
//	Vector2 limitSize = box1->size - box2->size;
//
//	return centerDistance.x <= limitSize.x && centerDistance.y <= limitSize.y;
//}
//
//bool CheckBoxWithPoint(BoxColliderComponent* box, Vector2& point)
//{
//	//算法：点与箱体中心点距离的绝对值 <= 箱体宽高一半
//	Vector2 centerDistance = (box->mBounds.mCenter - point).AbsThis();
//	Vector2 halfBoxSize = box->size / 2;
//
//	return centerDistance.x <= halfBoxSize.x &&
//		centerDistance.y <= halfBoxSize.y;
//}
//
//bool CheckBoxWithCircle(BoxColliderComponent* box, CircleColliderComponent* circle)
//{
//	//矩形左上角、右下角坐标
//	Vector2 topLeft = box->mBounds.mCenter - box->size / 2;
//	Vector2 bottomRight = box->mBounds.mCenter + box->size / 2;
//
//	//算法1：矩形顶点在圆内，离圆心最近尖角距离小于圆半径
//	Vector2 minV;		//与圆心距离最近的角，角和圆心的距离
//	minV.x = fminf(fabsf(topLeft.x - circle->mBounds.mCenter.x), fabsf(bottomRight.x - circle->mBounds.mCenter.x));
//	minV.y = fminf(fabsf(topLeft.y - circle->mBounds.mCenter.y), fabsf(bottomRight.y - circle->mBounds.mCenter.y));
//	if (minV.LengthUNSquared() < (circle->radius * circle->radius))
//		return true;
//
//	//算法2：圆与矩形边相交
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

