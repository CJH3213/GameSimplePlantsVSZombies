#pragma once
#include "ComponentBase.h"
#include "BoxCollider.h"

class ProjectilePeaScript :
	public ComponentBase
{
private:
	// 子弹移动速度（像素每秒）
	float mSpeed = 100.0f;
	// 上一帧时间（用来求两帧间隔）
	float mLastTime = 0.0f;

	// 子弹伤害值
	float mDamage = 20.0f;

	// 子弹自身碰撞器引用
	BoxCollider* mCollider = nullptr;

public:

	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 脚本初始化
	virtual void Awake() override;
	// 逻辑更新
	virtual void Update() override;

	// 碰撞开始回调
	void CollisionEnter(ICollider* other);
};

