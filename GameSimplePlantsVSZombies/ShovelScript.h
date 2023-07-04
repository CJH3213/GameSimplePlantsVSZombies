#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "PlantsManager.h"

class ShovelScript :
	public ComponentBase
{
private:
	// ����ʹ��������
	bool mIsUsing = false;

	// ֲ�������
	PlantsManager* mPlantManager = nullptr;

public:
	// ��ť���
	Button* mBtn = nullptr;

	// �ű���ʼ��
	virtual void Awake() override;

	// �߼�ѭ��
	virtual void Update() override;

	// ����ص�
	void OnClick();
};

