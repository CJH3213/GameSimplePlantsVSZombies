#pragma once
#include "ComponentBase.h"
#include "Vector2.h"

/// <summary>
/// 在草皮上随机产生阳光
/// </summary>
class SunCreatorScript :
	public ComponentBase
{
private:
	// 下次生成阳光的时间点
	float mNextTime = 0.0f;

public:
	// 左上草皮坐标
	Vector2 mGrassTLPos;
	// 右下角草皮坐标
	Vector2 mGrassBRPos;

	// 脚本初始化
	virtual void Awake() override;

	// 逻辑更新
	virtual void Update() override;
};

