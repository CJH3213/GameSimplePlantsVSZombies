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
	//记录填充条完整纹理宽度
	mWidth = mFillTexture->rectRgn.w;	
}

void SliderComponent::Update()
{
	if (mUpdateFlag == true)
	{
		mUpdateFlag = false;

		// 计算滑块位置
		float percent = GetPercent();
		int w = percent * mWidth;
		int x = (-mWidth) / 2 + w;
		// 设置滑块位置
		auto& handleTrans = mHandle->mTransform;
		handleTrans->localPosition.x = x;
		// 设置填充条裁切
		mFill->mTransform->localPosition.x = -(mWidth - w) / 2;	//左对齐
		mFillTexture->rectRgn.w = w;

		//调用回调
		OnValueChanged(this);
	}
}
