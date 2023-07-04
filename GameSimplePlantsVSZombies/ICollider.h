#pragma once
#include "Rectangle.h"

class ICollider
{
public:
	// �Ƿ�����
	virtual bool IsColliderEnable() = 0;

	// ��ײ�����������
	virtual void LateCollideUpdate() = 0;
	// ��ײ�ص�����
	virtual void OnCollisionCallback(ICollider*) = 0;

	// ��ȡ��ײ�������ص���Ϸ����
	virtual class GameObject* GetGameObj() = 0;
	// ��ȡ��ǰ��ײ���İ�Χ��
	virtual Rectangle GetBounds() = 0;
	// ����Ƿ�����һ����ײ���ཻ
	//virtual bool IsIntersectWithAABB(const Rectangle&) = 0;
};

