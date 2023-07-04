#include "LevelManager.h"
#include "PlantsManager.h"
#include "ZombiesManager.h"

void LevelManager::Instantiate()
{
	mName = "ActorsManager";

	// ֲ�������
	PlantsManager* plantManager = new PlantsManager();
	AddComponent(plantManager);
	plantManager->SetEnable(false);
	// ��ʬ������
	ZombiesManager* zombiesManager = new ZombiesManager();
	AddComponent(zombiesManager);
	zombiesManager->SetEnable(false);
}
