#include "LevelManager.h"
#include "PlantsManager.h"
#include "ZombiesManager.h"

void LevelManager::Instantiate()
{
	mName = "ActorsManager";

	// 植物管理器
	PlantsManager* plantManager = new PlantsManager();
	AddComponent(plantManager);
	plantManager->SetEnable(false);
	// 僵尸管理器
	ZombiesManager* zombiesManager = new ZombiesManager();
	AddComponent(zombiesManager);
	zombiesManager->SetEnable(false);
}
