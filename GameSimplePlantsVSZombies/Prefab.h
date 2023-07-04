#pragma once
#include "GameObject.h"

class Prefab :
	public GameObject
{
private:

public:
	// 构造函数
	Prefab();
	// 析构函数
	//~Prefab();

	// 预制件实例化写到这里
	virtual void Instantiate() {};
};

