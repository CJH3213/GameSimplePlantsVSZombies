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

	// 复制进度参数
	newComp->mInteractable = mInteractable;
	newComp->mMinValue = mMinValue;
	newComp->mMaxValue = mMaxValue;
	newComp->mValue = mValue;

	// 还有很多杂七杂八的不知道怎么复制

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
	// 限制当前值在最大值最小值之间
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
	//记录填充条原始大小
	mFillRect = mFillTexture->rectRgn;
}

void SliderComponent::Update()
{
	if (mUpdateFlag == true)
	{
		mUpdateFlag = false;

		// 计算滑块位置
		float percent = GetPercent();

		switch (mDirection)
		{
		case SliderComponent::LeftToRight:
		{
			float originW = mFillRect.w;
			float w = percent * originW;
			// 设置滑块位置
			mHandle->mTransform->localPosition.x = (-originW) / 2 + w;
			// 设置填充条裁切
			mFill->mTransform->localPosition.x = (-originW + w) / 2;	//左对齐
			mFillTexture->rectRgn.x = mFillRect.x;
			mFillTexture->rectRgn.w = w;	
		}break;

		case SliderComponent::RightToLeft:
		{
			float originW = mFillRect.w;
			float w = percent * originW;
			// 设置滑块位置
			mHandle->mTransform->localPosition.x = originW / 2 - w;
			// 设置填充条裁切
			mFill->mTransform->localPosition.x = (originW - w) / 2;	//右对齐
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

		//调用回调
		OnValueChanged(this);
	}
}
