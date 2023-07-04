#pragma once
#include <string>
#include "Prefab.h"

class CardInfo
{
public:
	// ֲ������
	std::string name = "Plant";
	// ���
	int amount = 0;
	// ��ȴʱ��
	float coolDown = 0;
	// ͷ��ͼƬ·��
	std::string resourceFolder = "";
	// ʵ����ֲԤ�Ƽ�
	Prefab* plantPrefab = nullptr;

	// ��������
	~CardInfo();
};

