#pragma once
#include "GameObject.h"
#include <vector>
#include "Prefab.h"

class CardBank :
	public Prefab
{
public:
	// 重写实例化方法
	virtual void Instantiate() override;
};
