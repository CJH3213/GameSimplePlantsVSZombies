#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "PlantsManager.h"

class SunflowerScript :
	public ComponentBase
{
private:
	// ������������24�����һ��25���⣩
	float mInterval = 24.0f;
	// ��¼�´�����ʱ���
	float mNextTime = 0.0f;

	// ֲ�������
	PlantsManager* mPlantManager = nullptr;

public:

	// ���
	virtual ComponentBase* Clone() const override;

	// �ű���ʼ��
	virtual void Awake() override;
	// �߼�����
	virtual void Update() override;

	// ����ֵ�仯�ص�
	void HPChange(float hp);
};

