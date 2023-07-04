#pragma once
//#include "ComponentBase.h"
#include "SliderComponent.h"

class Script01
	: public ComponentBase
{
private:
	// 草卷原始高度
	int handleHeight = 0;

public:
	// silder组件
	SliderComponent* mSliderComp = nullptr;

	// 脚本初始
	virtual void Awake() override;
	// 逻辑更新
	virtual void Update() override;

};

