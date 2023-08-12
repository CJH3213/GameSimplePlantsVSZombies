#include "LoadingSliderPrefab.h"
#include "TextureRender.h"
#include "SliderComponent.h"
#include "Script01.h"
#include "SceneBase.h"
#include "Game.h"

void LoadingSlider::Instantiate()
{
	Vector2 winSize = GetGame()->mWindow->GetSize();

	// 添加一个进度条
	GameObject* sliderGO = new GameObject("sliderGO");
	mScene->AddGameObject(sliderGO);
	sliderGO->mTransform->Translate(winSize / 2 + Vector2(0, 150), Space::World);

	// 背景条图片对象
	GameObject* sliderBackGO = new GameObject("");
	mScene->AddGameObject(sliderBackGO);
	sliderBackGO->SetParent(sliderGO);
	TextureRender* backRender = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("TitleScreen/LoadBar_dirt.png"));
	backRender->mOffset.y = 27;
	sliderBackGO->AddComponent(backRender);

	// 填充条图片对象
	GameObject* sliderFillGO = new GameObject("");
	mScene->AddGameObject(sliderFillGO);
	sliderFillGO->SetParent(sliderGO);
	TextureRender* grassRender = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("TitleScreen/LoadBar_grass.png"));
	grassRender->mOffset = Vector2(-10, 0);
	sliderFillGO->AddComponent(grassRender);

	// 滑块图片对象
	GameObject* sliderHandleGO = new GameObject("");
	mScene->AddGameObject(sliderHandleGO);
	sliderHandleGO->SetParent(sliderGO);
	TextureRender* rollCapRender = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("TitleScreen/SodRollCap.png"));
	rollCapRender->mOffset = Vector2(0, -25);
	sliderHandleGO->AddComponent(rollCapRender);

	// 添加Slider组件
	SliderComponent* sliderCP = new SliderComponent();
	sliderCP->SetFillRect(sliderFillGO);
	sliderCP->SetHandleRect(sliderHandleGO);
	sliderGO->AddComponent(sliderCP);
	sliderCP->SetValue(0.0f);	//设置滑块初值

	// 将脚本插入sliderGo游戏对象
	Script01* script = new Script01();
	script->mSliderComp = sliderGO->GetComponent<SliderComponent>();
	sliderGO->AddComponent(script);

}
