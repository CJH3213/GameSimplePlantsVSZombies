#pragma once
#include "ComponentBase.h"
#include "BoxCollider.h"

class PeashooterScript :
    public ComponentBase
{
private:
	// 发射豌豆间隔（2秒发射一颗豌豆）
	float mInterval = 1.4f;
	// 记录下次发射时间点
	float mNextTime = 0.0f;

	// 场景背景角色
	GameObject* mBackGround = nullptr;
	// 探测器碰撞组件
	BoxCollider* mDetectorCollider = nullptr;

	// 创建僵尸探测器
	void CreateDetector();
	// 获取探测器上的僵尸数量
	size_t GetZombiesNum();

public:

	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 脚本初始化
	virtual void Awake() override;
	// 逻辑更新
	virtual void Update() override;

	// 生命值变化回调
	void HPChange(float hp);
};

