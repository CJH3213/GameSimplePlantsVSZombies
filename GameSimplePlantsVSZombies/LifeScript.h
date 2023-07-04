#pragma once
#include "ComponentBase.h"
#include "EventHandlers.h"

class LifeScript :
	public ComponentBase
{
private:
	// 生命值
	float mHP = 100.0f;
	// 最小生命值
	float mMinHP = 0.0f;
	// 最大生命值
	float mMaxHP = 100.0f;

public:
	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 设置生命值范围
	void SetRange(float min, float max);
	// 增加生命值（输入负数减少生命值）
	void AddHP(float f);
	// 获取当前生命值
	float GetCurrHP() const { return mHP; };

	// 生命值变化事件监听
	EventHandlers<void(float hp)> mChangeEvents;
};

