#pragma once
//#include "ComponentBase.h"
#include "SliderComponent.h"

class Script01
	: public ComponentBase
{
private:
	// �ݾ�ԭʼ�߶�
	int handleHeight = 0;

public:
	// silder���
	SliderComponent* mSliderComp = nullptr;

	// �ű���ʼ
	virtual void Awake() override;
	// �߼�����
	virtual void Update() override;

};

