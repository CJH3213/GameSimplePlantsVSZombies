#pragma once
#include "ComponentBase.h"

class LevelBackGroundScript :
	public ComponentBase
{
public:
	// �������������������һ�ݣ�
	virtual ComponentBase* Clone() const override { return nullptr; };

	// �ű���ʼ��
	virtual void Awake() override;

	// ��Ӳݵ���ײ��
	void InstantiateCollider();
};

