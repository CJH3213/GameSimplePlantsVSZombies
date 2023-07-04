#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "PlantsManager.h"
#include "CardBankScript.h"

class TurfScript :
	public ComponentBase
{
private:
	// ��Ƭ����
	CardBankScript* mCardBank = nullptr;
	// ֲ�������
	PlantsManager* mPlantManager = nullptr;
	// Ԥ��ֲЧ������
	GameObject* mPreviewPlant = nullptr;
	// ����ֲֲ�����
	GameObject* mPlant = nullptr;
	// �Ժ����Ϲϵ�ֲ���Ҫ������ֲ���������

public:
	// ��ť���
	Button* mBtn = nullptr;

	// ���
	virtual ComponentBase* Clone() const override;

	// �ű���ʼ��
	virtual void Awake() override;

	// ����ֲ��
	void DestroyPlant();

	// �������
	void OnMouseEnter();
	// �������
	void OnMouseOver();
	// ����Ƴ�
	void OnMouseExit();
	// ����ص�
	void OnClick();
};

