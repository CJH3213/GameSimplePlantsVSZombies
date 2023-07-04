#pragma once
#include "SceneBase.h"

class AdventurePage
	: public SceneBase
{
private:

public:
	AdventurePage(std::string name);

	// 场景加载和实例化对象
	virtual void Start() override;
};

