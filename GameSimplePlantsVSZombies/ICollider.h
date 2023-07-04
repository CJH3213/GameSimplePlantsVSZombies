#pragma once
#include "Rectangle.h"

class ICollider
{
public:
	// 是否启用
	virtual bool IsColliderEnable() = 0;

	// 碰撞检测结束后调用
	virtual void LateCollideUpdate() = 0;
	// 碰撞回调函数
	virtual void OnCollisionCallback(ICollider*) = 0;

	// 获取碰撞器所挂载的游戏对象
	virtual class GameObject* GetGameObj() = 0;
	// 获取当前碰撞器的包围盒
	virtual Rectangle GetBounds() = 0;
	// 检查是否与另一个碰撞器相交
	//virtual bool IsIntersectWithAABB(const Rectangle&) = 0;
};

