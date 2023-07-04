#pragma once
#include "ComponentBase.h"
#include <functional>

class SliderComponent
	: public ComponentBase
{
private:
	// 可手动拖动
	bool mInteractable = true;
	// 最小值
	float mMinValue = 0.0f;
	// 最大值
	float mMaxValue = 1.0f;
	// 当前值
	float mValue = -1.0f;
	// 更新标志
	bool mUpdateFlag = true;

	// 行进宽度
	int mWidth = 0;
	// 填充区域的渲染组件
	class TextureRender* mFillRender = nullptr;
	// 填充区域纹理
	class Texture* mFillTexture = nullptr;

public:
	// 填充区域图形
	class GameObject* mFill = nullptr;
	// 滑块图形
	class GameObject* mHandle = nullptr;

	// 构造函数
	SliderComponent();
	// 析构函数
	~SliderComponent(){}
	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 设置数值区间
	void SetValueRange(float min, float max);
	//获取当前值
	float& GetValue() { return mValue; }
	// 获取当前值对应的百分比
	float GetPercent();
	// 设置当前值
	void SetValue(float f);
	// 设置填充区域图形对象
	void SetFillRect(class GameObject* obj) { mFill = obj; }
	// 设置滑块图形对象
	void SetHandleRect(class GameObject* obj) { mHandle = obj; }

	// 值变化回调
	std::function<void(SliderComponent*)>  OnValueChanged 
		= [](SliderComponent* slider){};

	// 组件初始化
	virtual void Awake() override;
	// 组件更新
	virtual void Update() override;
};

