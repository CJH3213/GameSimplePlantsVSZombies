#pragma once
#include <string>
#include "Prefab.h"

class CardInfo
{
public:
	// 植物名称
	std::string name = "Plant";
	// 金额
	int amount = 0;
	// 冷却时间
	float coolDown = 0;
	// 头像图片路径
	std::string resourceFolder = "";
	// 实际种植预制件
	Prefab* plantPrefab = nullptr;

	// 析构函数
	~CardInfo();
};

