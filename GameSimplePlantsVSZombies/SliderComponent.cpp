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
	f = Math::Clamp(f, mMinValue, mMaxValue);

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
	//��¼�����ԭʼ��С
	mFillRect = mFillTexture->rectRgn;
}

void SliderComponent::Update()
{
	if (mUpdateFlag == true)
	{
		mUpdateFlag = false;

		// ���㻬��λ��
		float percent = GetPercent();

		switch (mDirection)
		{
		case SliderComponent::LeftToRight:
		{
			float originW = mFillRect.w;
			float w = percent * originW;
			// ���û���λ��
			mHandle->mTransform->localPosition.x = (-originW) / 2 + w;
			// �������������
			mFill->mTransform->localPosition.x = (-originW + w) / 2;	//�����
			mFillTexture->rectRgn.x = mFillRect.x;
			mFillTexture->rectRgn.w = w;	
		}break;

		case SliderComponent::RightToLeft:
		{
			float originW = mFillRect.w;
			float w = percent * originW;
			// ���û���λ��
			mHandle->mTransform->localPosition.x = originW / 2 - w;
			// �������������
			mFill->mTransform->localPosition.x = (originW - w) / 2;	//�Ҷ���
			mFillTexture->rectRgn.x = originW - w + mFillRect.x;
			mFillTexture->rectRgn.w = w;
		}break;

		case SliderComponent::BottomToTop:
		{

		}break;

		case SliderComponent::TopToBottom:
		{

		}break;

		default:
			break;
		}

		//���ûص�
		OnValueChanged(this);
	}
}
