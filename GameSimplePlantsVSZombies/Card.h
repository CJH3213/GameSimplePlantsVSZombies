#pragma once
#include "GameObject.h"
#include "Prefab.h"
#include <vector>

/// <summary>
/// 卡片预制件
/// 不知道怎么实现预制件，先当做一个游戏对象
/// 注意：游戏逻辑只能写在脚本内，预制件只能用于实例化
/// </summary>
class Card :
	public Prefab
{
public:

	// 重写实例化方法
	virtual void Instantiate() override;
};

