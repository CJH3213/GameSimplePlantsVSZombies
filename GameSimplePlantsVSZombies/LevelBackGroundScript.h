#pragma once
#include "ComponentBase.h"

class LevelBackGroundScript :
	public ComponentBase
{
public:
	// 深拷贝（不拷贝，背景就一份）
	virtual ComponentBase* Clone() const override { return nullptr; };

	// 脚本初始化
	virtual void Awake() override;

	// 添加草地碰撞器
	void InstantiateCollider();
};

