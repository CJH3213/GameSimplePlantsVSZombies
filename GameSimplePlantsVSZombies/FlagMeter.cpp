#include "FlagMeter.h"
#include"SceneBase.h"
#include "TextureRender.h"
#include "Game.h"
#include "SliderComponent.h"

void FlagMeter::Instantiate()
{
	// 切割背景条和填充条图片


	// 背景条图片对象
	GameObject* sliderBackGO = new GameObject("");
	mScene->AddGameObject(sliderBackGO);
	sliderBackGO->SetParent(this);
	// 纹理渲染组件
	Texture* flagMeterTex1 = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/FlagMeter.png");
	flagMeterTex1->SetRectRgn({ 0, 0, 158, 26 });
	TextureRender* backRender = new TextureRender(flagMeterTex1);
	sliderBackGO->AddComponent(backRender);

	// 填充条图片对象
	GameObject* sliderFillGO = new GameObject("");
	mScene->AddGameObject(sliderFillGO);
	sliderFillGO->SetParent(this);
	// 纹理渲染组件
	Texture* flagMeterTex2 = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/FlagMeter.png");
	flagMeterTex2->SetRectRgn({ 0, 27, 158, 26 });
	TextureRender* grassRender = new TextureRender(flagMeterTex2);
	sliderFillGO->AddComponent(grassRender);

	// 滑块图片对象
	GameObject* sliderHandleGO = new GameObject("");
	mScene->AddGameObject(sliderHandleGO);
	sliderHandleGO->SetParent(this);
	// 纹理渲染组件
	Texture* flagMeterPartsTex1 = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/FlagMeterParts.png");
	flagMeterPartsTex1->SetRectRgn({ 0, 0, 25, 25 });
	TextureRender* rollCapRender = new TextureRender(flagMeterPartsTex1);
	sliderHandleGO->AddComponent(rollCapRender);

	// 添加Slider组件
	SliderComponent* sliderCP = new SliderComponent();
	this->AddComponent(sliderCP);
	sliderCP->SetFillRect(sliderFillGO);
	sliderCP->SetHandleRect(sliderHandleGO);
	sliderCP->SetValue(0.5f);	//设置滑块初值
}
