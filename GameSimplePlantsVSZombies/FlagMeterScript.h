#pragma once
#include "ComponentBase.h"
#include "Vector2.h"

class FlagMeterScript :
	public ComponentBase
{
private:
	// �������С
	Vector2 mFillSize;
	// ���ӻ������
	int mDrawOrder = 0;

public:
	// �ؿ��������ű�����
	class SliderComponent* mSlider = nullptr;
	// ���������������
	class GameObject* mFill = nullptr;

	// ���ý���
	void SetProgress(float value);
	// ��ӽڵ�����
	void AddFlag(float value);

	// �ű���ʼ��
	virtual void Awake() override;
};

