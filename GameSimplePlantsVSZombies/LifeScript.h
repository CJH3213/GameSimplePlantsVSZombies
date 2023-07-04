#pragma once
#include "ComponentBase.h"
#include "EventHandlers.h"

class LifeScript :
	public ComponentBase
{
private:
	// ����ֵ
	float mHP = 100.0f;
	// ��С����ֵ
	float mMinHP = 0.0f;
	// �������ֵ
	float mMaxHP = 100.0f;

public:
	// ���
	virtual ComponentBase* Clone() const override;

	// ��������ֵ��Χ
	void SetRange(float min, float max);
	// ��������ֵ�����븺����������ֵ��
	void AddHP(float f);
	// ��ȡ��ǰ����ֵ
	float GetCurrHP() const { return mHP; };

	// ����ֵ�仯�¼�����
	EventHandlers<void(float hp)> mChangeEvents;
};

