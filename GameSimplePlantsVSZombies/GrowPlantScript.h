#pragma once
#include "ComponentBase.h"
#include "PlantsManager.h"
#include "Prefab.h"
#include "PlantInfo.h"

class GrowPlantScript :
	public ComponentBase
{
private:
	// ֲ�������
	PlantsManager* mPlantManager = nullptr;

public:
	// �ж��Ƿ�����ֲ
	bool mIsPlanted = false;
	// ֲ����Ϣ
	PlantInfo mPlantInfo;

	// ���
	virtual ComponentBase* Clone() const override;

	// �ű���ʼ��
	virtual void Awake() override;

	// �߼�ѭ��
	virtual void Update() override;

};

