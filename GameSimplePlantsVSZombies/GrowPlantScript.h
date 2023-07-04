#pragma once
#include "ComponentBase.h"
#include "PlantsManager.h"
#include "Prefab.h"
#include "PlantInfo.h"

class GrowPlantScript :
	public ComponentBase
{
private:
	// 植物管理器
	PlantsManager* mPlantManager = nullptr;

public:
	// 判断是否已种植
	bool mIsPlanted = false;
	// 植物信息
	PlantInfo mPlantInfo;

	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 脚本初始化
	virtual void Awake() override;

	// 逻辑循环
	virtual void Update() override;

};

