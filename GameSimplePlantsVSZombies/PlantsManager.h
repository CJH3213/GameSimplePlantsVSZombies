#pragma once
#include "ComponentBase.h"
//#include "GrowPlant.h"

class PlantsManager :
	public ComponentBase
{

public:
	// 鼠标持有对象
	GameObject* mMouseHold = nullptr;

	// 对战开始后启用组件
	virtual void OnEnable() override;
};

