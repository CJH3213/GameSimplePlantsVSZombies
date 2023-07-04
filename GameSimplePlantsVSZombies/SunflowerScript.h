#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "PlantsManager.h"

class SunflowerScript :
	public ComponentBase
{
private:
	// 生产阳光间隔（24秒产生一个25阳光）
	float mInterval = 24.0f;
	// 记录下次生产时间点
	float mNextTime = 0.0f;

	// 植物管理器
	PlantsManager* mPlantManager = nullptr;

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

