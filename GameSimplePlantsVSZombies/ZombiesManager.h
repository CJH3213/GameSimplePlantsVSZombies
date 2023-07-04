#pragma once
#include "ComponentBase.h"
#include <array>
#include "Vector2.h"

class ZombiesManager :
	public ComponentBase
{
private:
	// 生成僵尸的间隔
	float mInterval = 10.0f;
	// 下次生成僵尸的时间
	float mNextTime = 0.0f;

	// 每行生成位置x
	std::array<float, 5> mBeginPos = {125, 225, 325, 425, 525};

	// 背景图片对象引用
	GameObject* mBackGround = nullptr;

public:
	// 对战开始后启用组件
	virtual void OnEnable() override;

	// 脚本初始化
	virtual void Start() override;
	// 逻辑更新
	virtual void Update() override;
};

