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
		// �ݾ�ı任���
		auto& handleTrans = slider->mHandle->mTransform;
		float percent = slider->GetPercent();
		// �ݾ���ת
		handleTrans->localRotation = percent * 360.0f * 1.8f;
		// �ݾ��С
		float scale = Vector2::LinearEquation(percent, Vector2(0, 1), Vector2(1, 0.5f));
		handleTrans->localScale = Vector2(1, 1) * scale;
		// �ݾ�λ�ã��׶��룩
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
