#pragma once
#include "Prefab.h"

class LevelBackGround :
	public Prefab
{
public:
	// 重写实例化方法
	virtual void Instantiate() override;
};

