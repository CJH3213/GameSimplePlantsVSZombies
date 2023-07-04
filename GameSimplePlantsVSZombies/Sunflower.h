#pragma once
#include "Prefab.h"

class Sunflower :
	public Prefab
{
public:
	// 预制件实例化写到这里
	virtual void Instantiate() override;
};

