#include "FlagMeter.h"
#include"SceneBase.h"
#include "TextureRender.h"
#include "Game.h"
#include "SliderComponent.h"

void FlagMeter::Instantiate()
{
	// �и�����������ͼƬ


	// ������ͼƬ����
	GameObject* sliderBackGO = new GameObject("");
	mScene->AddGameObject(sliderBackGO);
	sliderBackGO->SetParent(this);
	// ������Ⱦ���
	Texture* flagMeterTex1 = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/FlagMeter.png");
	flagMeterTex1->SetRectRgn({ 0, 0, 158, 26 });
	TextureRender* backRender = new TextureRender(flagMeterTex1);
	sliderBackGO->AddComponent(backRender);

	// �����ͼƬ����
	GameObject* sliderFillGO = new GameObject("");
	mScene->AddGameObject(sliderFillGO);
	sliderFillGO->SetParent(this);
	// ������Ⱦ���
	Texture* flagMeterTex2 = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/FlagMeter.png");
	flagMeterTex2->SetRectRgn({ 0, 27, 158, 26 });
	TextureRender* grassRender = new TextureRender(flagMeterTex2);
	sliderFillGO->AddComponent(grassRender);

	// ����ͼƬ����
	GameObject* sliderHandleGO = new GameObject("");
	mScene->AddGameObject(sliderHandleGO);
	sliderHandleGO->SetParent(this);
	// ������Ⱦ���
	Texture* flagMeterPartsTex1 = GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/FlagMeterParts.png");
	flagMeterPartsTex1->SetRectRgn({ 0, 0, 25, 25 });
	TextureRender* rollCapRender = new TextureRender(flagMeterPartsTex1);
	sliderHandleGO->AddComponent(rollCapRender);

	// ���Slider���
	SliderComponent* sliderCP = new SliderComponent();
	this->AddComponent(sliderCP);
	sliderCP->SetFillRect(sliderFillGO);
	sliderCP->SetHandleRect(sliderHandleGO);
	sliderCP->SetValue(0.5f);	//���û����ֵ
}
