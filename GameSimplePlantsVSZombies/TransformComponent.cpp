#include "TransformComponent.h"
#include "GameObject.h"
#include "SceneBase.h"

#pragma region CreateAndDestroy
/// <summary>
/// 构造Transform，指定初始坐标、初始角度、初始缩放比例
/// </summary>
/// <param name="name"></param>
/// <param name="gameobject"></param>
/// <param name="p">初始坐标</param>
/// <param name="r">初始角度</param>
/// <param name="s">初始缩放</param>
TransformComponent::TransformComponent(
	TransformComponent* parentTrans,
	const Vector2& p, float r, const Vector2& s)
{
	localPosition = p;
	localRotation = r;
	localScale = s;

	mParentTrans = parentTrans;
}

TransformComponent::TransformComponent(
	 TransformComponent* parentTrans)
	:TransformComponent(parentTrans, Vector2(0,0), 0, Vector2(1, 1))
{
}

TransformComponent::TransformComponent() :
	TransformComponent(nullptr)
{
}

TransformComponent::~TransformComponent()
{
	// 与父对象 解除 关系
	if (mParentTrans)
	{
		auto& vec = mParentTrans->mChildren;
		auto iter = std::find(vec.begin(), vec.end(), this);
		if (iter != vec.end())
			vec.erase(iter);

		mParentTrans = nullptr;
	}
		
	// 解除当前对象的子对象关系
	for (auto child : mChildren)
	{
		child->mParentTrans = nullptr;
	}

	mChildren.clear();
}

ComponentBase* TransformComponent::Clone() const
{
	TransformComponent* newComp = new TransformComponent();

	//子变换组件引用先清空，不要复制现在的
	newComp->mChildren.clear();

	// 设置相对变换属性
	newComp->localPosition = localPosition;
	newComp->localRotation = localRotation;
	newComp->localScale = localScale;

	// 父对象变换组件引用先保持空指针
	// 游戏对象时会设置父对象

	return newComp;
}

#pragma endregion



#pragma region Translate

/// <summary>
/// 移动
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="relativeTo">相对坐标系：Self自身（与原坐标的偏移）、Parent父物体（相对坐标）、World世界（绝对坐标）</param>
void TransformComponent::Translate(float x, float y, Space relativeTo)
{
	//相对自身当前坐标移动，增量
	if (relativeTo == Space::Self)
	{
		localPosition.x += x;
		localPosition.y += y;
	}
	//相对父，直接赋值当前相对位置
	else if (relativeTo == Space::Parent)
	{
		localPosition.x = x;
		localPosition.y = y;
	}
	//相对世界原点移动
	else 
	{
		SetPosition(Vector2(x, y));
	}
}

/// <summary>
/// 移动
/// </summary>
/// <param name="v"></param>
/// <param name="relativeTo">相对坐标系：Self自身（与原坐标的偏移）、Parent父物体（相对坐标）、World世界（绝对坐标）</param>
void TransformComponent::Translate(const Vector2& v, Space relativeTo)
{
	Translate(v.x, v.y, relativeTo);
}
#pragma endregion


#pragma region Rotate
/// <summary>
/// 旋转
/// </summary>
/// <param name="angle">角度</param>
/// <param name="relativeTo">相对坐标系：Self自身（与原坐标的偏移）、Parent父物体（相对坐标）、World世界（绝对坐标）</param>
void TransformComponent::Rotate(float angle, Space relativeTo)
{
	//自己绕中点旋转
	if (relativeTo == Space::Self)
	{
		localRotation = angle;
	}
	//自己不转，物体围绕父点旋转
	else if(relativeTo == Space::Parent)
	{
		Vector2 v;
		v.x = localPosition.x * cosf(angle) - localPosition.y * sinf(angle);
		v.y = localPosition.x * sinf(angle) + localPosition.y * cosf(angle);
		//向量旋转公式
		//x' = xcosα - ysinα;
		//y' = xsinα + ycosα;
	}
	else if (relativeTo == Space::World)
	{
		Vector2 v;
		Vector2 pos = GetPosition();
		v.x = pos.x * cosf(angle) - pos.y * sinf(angle);
		v.y = pos.x * sinf(angle) + pos.y * cosf(angle);
		SetPosition(v);
	}
}

/// <summary>
/// 围绕指定点旋转
/// </summary>
/// <param name="angle"></param>
/// <param name="v"></param>
void TransformComponent::RotateAround(float angle, const Vector2& v)
{
	//先相对于世界坐标旋转（0,0）
	Rotate(angle, Space::World);
	//再与目标坐标叠加
	Translate(v, Space::Self);
}

/// <summary>
/// 转向（看向）目标点
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
bool TransformComponent::LookAt(const Vector2& v)
{
	//计算两向量角度：
	//由几何点积公式a·b=|a||b|cosθ
	//得出θ=acos(a·b / |a||b|)
	float deno = localPosition.LengthSquared() * v.LengthSquared();	//a模长*b模长
	if (Math::NearZero(deno))	//防止分母为0
		return false;
	float angle = acosf(localPosition.Dot(v) / deno);
	//将当前物体旋转向v
	Rotate(angle, Space::Self);
	return true;
}
#pragma endregion


#pragma region Scale
/// <summary>
/// 缩放
/// </summary>
/// <param name="v">x、y两方向上的缩放比例</param>
/// <param name="relativeTo">相对坐标系：Model模型（与模型的缩放比例）、Self自身（与原坐标的偏移）、Parent父物体（相对坐标）、World世界（绝对坐标）</param>
void TransformComponent::Scale(const Vector2& v, Space relativeTo)
{
	//相对于原模型的缩放比例
	if (relativeTo == Space::Model)
		localScale = v;
	//相对于当前的追加缩放比例
	else
	{
		localScale.x *= v.x;
		localScale.y *= v.y;
	}
}

/// <summary>
/// 等比缩放
/// </summary>
/// <param name="f"></param>
/// <param name="relativeTo"></param>
void TransformComponent::Scale(float f, Space relativeTo)
{
	Scale(Vector2(f, f), relativeTo);
}

void TransformComponent::SetParent(TransformComponent* parent)
{
	// 移除之前设置的父关系
	if (mParentTrans != nullptr)
	{
		auto parentChildren = mParentTrans->mChildren;
		auto it = std::find(parentChildren.begin(), parentChildren.end(), this);
		if(it != parentChildren.end())
			parentChildren.erase(it);

		mParentTrans = nullptr;
	}

	// 记录父对象的变换组件
	mParentTrans = parent;

	// 向父对象记录子对象
	if(parent != nullptr)
		parent->mChildren.emplace_back(this);

}

size_t TransformComponent::ChildCount()
{
	return mChildren.size();
}

TransformComponent* TransformComponent::GetChild(size_t index)
{
	return mChildren.at(index);
}

Vector2 TransformComponent::GetPosition() const
{
	TransformComponent* parent = mParentTrans;
	Vector2 posSum = localPosition;
	while (parent)
	{
		posSum += parent->localPosition;
		parent = parent->mParentTrans;
	}

	return posSum;
}

void TransformComponent::SetPosition(Vector2 p)
{
	TransformComponent* parent = mParentTrans;
	while (parent)
	{
		p -= parent->localPosition;
		parent = parent->mParentTrans;
	}
	localPosition = p;
}

void TransformComponent::SetRotation(float f)
{
	TransformComponent* parent = mParentTrans;
	while (parent)
	{
		f -= parent->localRotation;
		parent = parent->mParentTrans;
	}
	localRotation = f;
}

float TransformComponent::GetRotation() const
{
	TransformComponent* parent = mParentTrans;
	float rotSum = localRotation;
	while (parent)
	{
		rotSum += parent->localRotation;
		parent = parent->mParentTrans;
	}
	return rotSum;
}

void TransformComponent::SetScale(Vector2 v)
{
	TransformComponent* parent = mParentTrans;
	while (parent)
	{
		v /= parent->localScale;
		parent = parent->mParentTrans;
	}
	localScale = v;
}

Vector2 TransformComponent::GetScale() const
{
	TransformComponent* parent = mParentTrans;
	Vector2 scaSum = localScale;
	while (parent)
	{
		scaSum *= parent->localScale;
		parent = parent->mParentTrans;
	}

	return scaSum;
}

#pragma endregion

