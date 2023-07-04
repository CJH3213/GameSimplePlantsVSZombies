#include "ChooseBox.h"
#include"SceneBase.h"
#include "TextureRender.h"
#include "TextComponent.h"
#include "ImageButton.h"
#include "ChooseBoxScript.h"
#include "Animator.h"
#include "Game.h"
#include "AudioSource.h"

void ChooseBox::Instantiate()
{
	// 退场坐标
	Vector2 exitPos = { -233, 344 };
	// 登场坐标
	Vector2 entryPos = { 233, 344 };

	// 添加选卡栏
	GameObject* chooseBoxG = new GameObject("ChooseBox");
	mScene->AddGameObject(chooseBoxG);		//添加对象到场景
	chooseBoxG->mTransform->localPosition = exitPos;

	// 背景
	GameObject* chooseBoxBgG = new GameObject("chooseBoxBgG");
	mScene->AddGameObject(chooseBoxBgG);		//添加对象到场景
	chooseBoxBgG->SetParent(chooseBoxG);
	TextureRender* chooseBoxBgTexC = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath(
		"AdventureScreen/SeedChooser_Background.png"));
	chooseBoxBgG->AddComponent(chooseBoxBgTexC);

	// 标题
	GameObject* chooseBoxTitleG = new GameObject("chooseBoxTitleG");
	mScene->AddGameObject(chooseBoxTitleG);		//添加对象到场景
	chooseBoxTitleG->SetParent(chooseBoxG);		//设置父对象
	chooseBoxTitleG->mTransform->localPosition = { 0, -240 };
	FontStyle textStyle02;		//字体样式
	textStyle02.size = 20;
	textStyle02.color = { 255, 213, 159, 43 };
	TextComponent* chooseBoxTitleC = new TextComponent(
		L"选择你的植物", textStyle02);
	chooseBoxTitleG->AddComponent(chooseBoxTitleC);		//添加文本组件

	// 按钮
	GameObject* chooseBoxBtnG = new GameObject("chooseBoxBtnG");
	mScene->AddGameObject(chooseBoxBtnG);
	chooseBoxBtnG->SetParent(chooseBoxG);
	chooseBoxBtnG->mTransform->localPosition = { 0, 190 };
	ImageButton* chooseBoxBtnC = new ImageButton(
		"AdventureScreen/SeedChooser_Button_Disabled.png",
		"AdventureScreen/SeedChooser_Button.png",
		"AdventureScreen/SeedChooser_Button.png");
	chooseBoxBtnG->AddComponent(chooseBoxBtnC);		// 添加按钮组件
	FontStyle textStyle03;	//字体样式
	textStyle03.size = 20;
	textStyle03.color = { 255, 213, 159, 43 };
	TextComponent* chooseBoxBtnTextC = new TextComponent(
		L"一起摇滚！", textStyle03);
	chooseBoxBtnG->AddComponent(chooseBoxBtnTextC);	//添加文本组件

	// 添加动作组件（该组件和脚本同层，方便获取）
	Animator* bgAnimCom = new Animator();
	chooseBoxG->AddComponent(bgAnimCom);
	// 向右登场
	bgAnimCom->AddKeyframe("Entry", {
		{0.0f, exitPos},
		{0.5f, entryPos, 0.0f, {1.0f, 1.0f},
			[this, bgAnimCom] {}},
		});
	// 向左退场
	bgAnimCom->AddKeyframe("Exit", {
		{0.0f, entryPos},
		{0.5f, exitPos, 0.0f, {1.0f, 1.0f},
			[this, bgAnimCom] {}},
		});


	// 添加背景音乐
	AudioSource* audio = new AudioSource();
	AddComponent(audio);

	// 脚本
	ChooseBoxScript* script = new ChooseBoxScript();
	script->mStartBtn = chooseBoxBtnC;
	script->mAudio = audio;
	chooseBoxG->AddComponent(script);
}
