#pragma once
#include "ComponentBase.h"
#include "Vector2.h"

class FlagMeterScript :
	public ComponentBase
{
private:
	// 填充条大小
	Vector2 mFillSize;
	// 旗子绘制深度
	int mDrawOrder = 0;

public:
	// 关卡进度条脚本引用
	class SliderComponent* mSlider = nullptr;
	// 进度填充块对象引用
	class GameObject* mFill = nullptr;

	// 设置进度
	void SetProgress(float value);
	// 添加节点旗帜
	void AddFlag(float value);

	// 脚本初始化
	virtual void Awake() override;
};

