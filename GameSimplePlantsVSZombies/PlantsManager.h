#pragma once
#include "ComponentBase.h"
//#include "GrowPlant.h"

class PlantsManager :
	public ComponentBase
{

public:
	// �����ж���
	GameObject* mMouseHold = nullptr;

	// ��ս��ʼ���������
	virtual void OnEnable() override;
};

