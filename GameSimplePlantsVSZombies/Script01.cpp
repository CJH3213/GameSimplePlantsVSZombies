#include "Script01.h"
#include "GameObject.h"
#include "TextureRender.h"
#include "Game.h"
#include "MainMenuScene.h"

void Script01::Awake()
{
	handleHeight = mSliderComp->mHandle->GetComponent<TextureRender>()->mTexture->GetHeight();
	mSliderComp->OnValueChanged =
		[this](SliderComponent* slider)
	{
		// 草卷的变换组件
		auto& handleTrans = slider->mHandle->mTransform;
		float percent = slider->GetPercent();
		// 草卷旋转
		handleTrans->localRotation = percent * 360.0f * 1.8f;
		// 草卷变小
		float scale = Vector2::LinearEquation(percent, Vector2(0, 1), Vector2(1, 0.5f));
		handleTrans->localScale = Vector2(1, 1) * scale;
		// 草卷位置（底对齐）
		int y = Vector2::LinearEquation(percent, Vector2(0, 0), Vector2(1, 42));
		handleTrans->localPosition.y = y;
	};
}

void Script01::Update()
{
	float& value = mSliderComp->GetValue();
	mSliderComp->SetValue(value + 0.003);

	if (value >= 1.0f)
	{
		auto game = GetGame();
		game->mSceneManager->LoadScene(new MainMenuScene("Main"));
	}
}
