#pragma once
#include "ColliderBase.h"

class BoxCollider :
   public ColliderBase
{
public:
	// 矩形碰撞器大小
	Vector2 mSize = {10, 10};

	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 获取当前碰撞器的包围盒
	virtual Rectangle GetBounds() override;
};

