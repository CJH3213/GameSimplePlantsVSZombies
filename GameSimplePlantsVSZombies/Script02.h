#pragma once
#include "ComponentBase.h"
#include "ImageButton.h"
#include "TextButton.h"

class Script02
	: public ComponentBase
{
private:

public:
	// 开始冒险按钮
	ImageButton* mBtnStart = nullptr;
	// 退出按钮
	ImageButton* mBtnExit = nullptr;

	// 脚本初始化
	virtual void Awake() override;
};

