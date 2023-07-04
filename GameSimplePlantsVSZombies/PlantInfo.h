#pragma once
#include <string>
#include "Prefab.h"

struct PlantInfo
{
	// 植物名称
	std::string mName = "";
	// 植物对象资源文件夹路径
	std::string mResourceFolder = "";
	// 实际植物预制件
	Prefab* mPlantPrefab = nullptr;
};

