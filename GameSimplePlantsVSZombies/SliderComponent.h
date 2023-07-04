#pragma once
#include "ComponentBase.h"
#include <functional>

class SliderComponent
	: public ComponentBase
{
private:
	// ���ֶ��϶�
	bool mInteractable = true;
	// ��Сֵ
	float mMinValue = 0.0f;
	// ���ֵ
	float mMaxValue = 1.0f;
	// ��ǰֵ
	float mValue = -1.0f;
	// ���±�־
	bool mUpdateFlag = true;

	// �н����
	int mWidth = 0;
	// ����������Ⱦ���
	class TextureRender* mFillRender = nullptr;
	// �����������
	class Texture* mFillTexture = nullptr;

public:
	// �������ͼ��
	class GameObject* mFill = nullptr;
	// ����ͼ��
	class GameObject* mHandle = nullptr;

	// ���캯��
	SliderComponent();
	// ��������
	~SliderComponent(){}
	// ���
	virtual ComponentBase* Clone() const override;

	// ������ֵ����
	void SetValueRange(float min, float max);
	//��ȡ��ǰֵ
	float& GetValue() { return mValue; }
	// ��ȡ��ǰֵ��Ӧ�İٷֱ�
	float GetPercent();
	// ���õ�ǰֵ
	void SetValue(float f);
	// �����������ͼ�ζ���
	void SetFillRect(class GameObject* obj) { mFill = obj; }
	// ���û���ͼ�ζ���
	void SetHandleRect(class GameObject* obj) { mHandle = obj; }

	// ֵ�仯�ص�
	std::function<void(SliderComponent*)>  OnValueChanged 
		= [](SliderComponent* slider){};

	// �����ʼ��
	virtual void Awake() override;
	// �������
	virtual void Update() override;
};

