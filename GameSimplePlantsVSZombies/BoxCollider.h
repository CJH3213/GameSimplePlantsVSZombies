#pragma once
#include "ColliderBase.h"

class BoxCollider :
   public ColliderBase
{
public:
	// ������ײ����С
	Vector2 mSize = {10, 10};

	// ���
	virtual ComponentBase* Clone() const override;

	// ��ȡ��ǰ��ײ���İ�Χ��
	virtual Rectangle GetBounds() override;
};

