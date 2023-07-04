#include "TransformComponent.h"
#include "GameObject.h"
#include "SceneBase.h"

#pragma region CreateAndDestroy
/// <summary>
/// ����Transform��ָ����ʼ���ꡢ��ʼ�Ƕȡ���ʼ���ű���
/// </summary>
/// <param name="name"></param>
/// <param name="gameobject"></param>
/// <param name="p">��ʼ����</param>
/// <param name="r">��ʼ�Ƕ�</param>
/// <param name="s">��ʼ����</param>
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
	// �븸���� ��� ��ϵ
	if (mParentTrans)
	{
		auto& vec = mParentTrans->mChildren;
		auto iter = std::find(vec.begin(), vec.end(), this);
		if (iter != vec.end())
			vec.erase(iter);

		mParentTrans = nullptr;
	}
		
	// �����ǰ������Ӷ����ϵ
	for (auto child : mChildren)
	{
		child->mParentTrans = nullptr;
	}

	mChildren.clear();
}

ComponentBase* TransformComponent::Clone() const
{
	TransformComponent* newComp = new TransformComponent();

	//�ӱ任�����������գ���Ҫ�������ڵ�
	newComp->mChildren.clear();

	// ������Ա任����
	newComp->localPosition = localPosition;
	newComp->localRotation = localRotation;
	newComp->localScale = localScale;

	// ������任��������ȱ��ֿ�ָ��
	// ��Ϸ����ʱ�����ø�����

	return newComp;
}

#pragma endregion



#pragma region Translate

/// <summary>
/// �ƶ�
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="relativeTo">�������ϵ��Self������ԭ�����ƫ�ƣ���Parent�����壨������꣩��World���磨�������꣩</param>
void TransformComponent::Translate(float x, float y, Space relativeTo)
{
	//�������ǰ�����ƶ�������
	if (relativeTo == Space::Self)
	{
		localPosition.x += x;
		localPosition.y += y;
	}
	//��Ը���ֱ�Ӹ�ֵ��ǰ���λ��
	else if (relativeTo == Space::Parent)
	{
		localPosition.x = x;
		localPosition.y = y;
	}
	//�������ԭ���ƶ�
	else 
	{
		SetPosition(Vector2(x, y));
	}
}

/// <summary>
/// �ƶ�
/// </summary>
/// <param name="v"></param>
/// <param name="relativeTo">�������ϵ��Self������ԭ�����ƫ�ƣ���Parent�����壨������꣩��World���磨�������꣩</param>
void TransformComponent::Translate(const Vector2& v, Space relativeTo)
{
	Translate(v.x, v.y, relativeTo);
}
#pragma endregion


#pragma region Rotate
/// <summary>
/// ��ת
/// </summary>
/// <param name="angle">�Ƕ�</param>
/// <param name="relativeTo">�������ϵ��Self������ԭ�����ƫ�ƣ���Parent�����壨������꣩��World���磨�������꣩</param>
void TransformComponent::Rotate(float angle, Space relativeTo)
{
	//�Լ����е���ת
	if (relativeTo == Space::Self)
	{
		localRotation = angle;
	}
	//�Լ���ת������Χ�Ƹ�����ת
	else if(relativeTo == Space::Parent)
	{
		Vector2 v;
		v.x = localPosition.x * cosf(angle) - localPosition.y * sinf(angle);
		v.y = localPosition.x * sinf(angle) + localPosition.y * cosf(angle);
		//������ת��ʽ
		//x' = xcos�� - ysin��;
		//y' = xsin�� + ycos��;
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
/// Χ��ָ������ת
/// </summary>
/// <param name="angle"></param>
/// <param name="v"></param>
void TransformComponent::RotateAround(float angle, const Vector2& v)
{
	//�����������������ת��0,0��
	Rotate(angle, Space::World);
	//����Ŀ���������
	Translate(v, Space::Self);
}

/// <summary>
/// ת�򣨿���Ŀ���
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
bool TransformComponent::LookAt(const Vector2& v)
{
	//�����������Ƕȣ�
	//�ɼ��ε����ʽa��b=|a||b|cos��
	//�ó���=acos(a��b / |a||b|)
	float deno = localPosition.LengthSquared() * v.LengthSquared();	//aģ��*bģ��
	if (Math::NearZero(deno))	//��ֹ��ĸΪ0
		return false;
	float angle = acosf(localPosition.Dot(v) / deno);
	//����ǰ������ת��v
	Rotate(angle, Space::Self);
	return true;
}
#pragma endregion


#pragma region Scale
/// <summary>
/// ����
/// </summary>
/// <param name="v">x��y�������ϵ����ű���</param>
/// <param name="relativeTo">�������ϵ��Modelģ�ͣ���ģ�͵����ű�������Self������ԭ�����ƫ�ƣ���Parent�����壨������꣩��World���磨�������꣩</param>
void TransformComponent::Scale(const Vector2& v, Space relativeTo)
{
	//�����ԭģ�͵����ű���
	if (relativeTo == Space::Model)
		localScale = v;
	//����ڵ�ǰ��׷�����ű���
	else
	{
		localScale.x *= v.x;
		localScale.y *= v.y;
	}
}

/// <summary>
/// �ȱ�����
/// </summary>
/// <param name="f"></param>
/// <param name="relativeTo"></param>
void TransformComponent::Scale(float f, Space relativeTo)
{
	Scale(Vector2(f, f), relativeTo);
}

void TransformComponent::SetParent(TransformComponent* parent)
{
	// �Ƴ�֮ǰ���õĸ���ϵ
	if (mParentTrans != nullptr)
	{
		auto parentChildren = mParentTrans->mChildren;
		auto it = std::find(parentChildren.begin(), parentChildren.end(), this);
		if(it != parentChildren.end())
			parentChildren.erase(it);

		mParentTrans = nullptr;
	}

	// ��¼������ı任���
	mParentTrans = parent;

	// �򸸶����¼�Ӷ���
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

