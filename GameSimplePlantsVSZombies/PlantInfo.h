#pragma once
#include <string>
#include "Prefab.h"

struct PlantInfo
{
	// ֲ������
	std::string mName = "";
	// ֲ�������Դ�ļ���·��
	std::string mResourceFolder = "";
	// ʵ��ֲ��Ԥ�Ƽ�
	Prefab* mPlantPrefab = nullptr;
};

