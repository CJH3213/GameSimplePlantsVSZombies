#include "SliderComponent.h"
#include "MathBase.h"
#include "GameObject.h"
#include "TextureRender.h"

SliderComponent::SliderComponent()
{
}

ComponentBase* SliderComponent::Clone() const
{
	SliderComponent* newComp = new SliderComponent();

	// ���ƽ��Ȳ���
	newComp->mInteractable = mInteractable;
	newComp->mMinValue = mMinValue;
	newComp->mMaxValue = mMaxValue;
	newComp->mValue = mValue;

	// ���кܶ������Ӱ˵Ĳ�֪����ô����

	return newComp;
}

void SliderComponent::SetValueRange(float min, float max)
{
	mMinValue = min;
	mMaxValue = max;
}

float SliderComponent::GetPercent()
{
	return (mValue - mMinValue) / (mMaxValue - mMinValue);
}

void SliderComponent::SetValue(float f)
{
	// ���Ƶ�ǰֵ�����ֵ��Сֵ֮��
	f = Math::Max(f, mMinValue);
	f = Math::Min(f, mMaxValue);

	if (mValue != f)
	{
		mValue = f;
		mUpdateFlag = true;
	}
}

void SliderComponent::Awake()
{
	mFillRender = mFill->GetComponent<TextureRender>();
	mFillTexture = mFillRender->mTexture;
	//��¼���������������
	mWidth = mFillTexture->rectRgn.w;	
}

void SliderComponent::Update()
{
	if (mUpdateFlag == true)
	{
		mUpdateFlag = false;

		// ���㻬��λ��
		float percent = GetPercent();
		int w = percent * mWidth;
		int x = (-mWidth) / 2 + w;
		// ���û���λ��
		auto& handleTrans = mHandle->mTransform;
		handleTrans->localPosition.x = x;
		// �������������
		mFill->mTransform->localPosition.x = -(mWidth - w) / 2;	//�����
		mFillTexture->rectRgn.w = w;

		//���ûص�
		OnValueChanged(this);
	}
}
