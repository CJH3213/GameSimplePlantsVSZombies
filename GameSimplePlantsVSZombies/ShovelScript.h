#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "PlantsManager.h"

class ShovelScript :
	public ComponentBase
{
private:
	// 正在使用铁铲吗？
	bool mIsUsing = false;

	// 植物管理器
	PlantsManager* mPlantManager = nullptr;

public:
	// 按钮组件
	Button* mBtn = nullptr;

	// 脚本初始化
	virtual void Awake() override;

	// 逻辑循环
	virtual void Update() override;

	// 点击回调
	void OnClick();
};

