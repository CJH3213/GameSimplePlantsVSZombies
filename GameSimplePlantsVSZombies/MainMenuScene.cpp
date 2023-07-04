#include "MainMenuScene.h"
#include "Game.h"
#include "TextureRender.h"
#include "GraveButton.h"
#include "TextComponent.h"
#include "Script02.h"

MainMenuScene::MainMenuScene(std::string name) :
	SceneBase(name)
{
}

void MainMenuScene::Start()
{
	// 获取窗口大小
	Vector2 windowSize = GetGame()->mWindow->GetSize();

	// 加载背景图片
	GameObject* backGround = new GameObject("bgImgO");
	backGround->mTransform->Translate(windowSize / 2, Space::World);	//设置背景图居中在窗口
	AddGameObject(backGround);
	// 添加渲染组件
	TextureRender* bgRenCom = new TextureRender(
		GetGame()->mImageManagement->GetTextureByPath(
		"SelectorScreen/Surface.png"));
	backGround->AddComponent(bgRenCom);

	// 加载开始冒险按钮
	GameObject* btStarAdventure = new GameObject("StarAdventureG");
	btStarAdventure->SetParent(backGround);	//背景图为按钮的父对象
	btStarAdventure->mTransform->localPosition = Vector2(170, -160);
	AddGameObject(btStarAdventure);
	// 添加按钮组件
	GraveButton* btStartBtnCom = new GraveButton(
		"SelectorScreen/SelectorScreen_StartAdventure_Button1.png",
		"SelectorScreen/SelectorScreen_StartAdventure_Highlight.png");
	btStarAdventure->AddComponent(btStartBtnCom);

	// 退出按钮
	GameObject* btExit = new GameObject("ExitG");
	btExit->SetParent(backGround);	//背景图为按钮的父对象
	btExit->mTransform->localPosition = Vector2(345, 225);
	AddGameObject(btExit);
	// 添加文字按钮组件
	FontStyle textSty01;
	textSty01.size = 23;
	FontStyle textSty02;
	textSty02.size = 30;
	textSty02.color = Color::Green;
	TextButton* btExitBtnCom = new TextButton(
		L"退出", textSty01, textSty02);
	btExit->AddComponent(btExitBtnCom);

	// 脚本02
	Script02* script = new Script02();
	script->mBtnStart = btStartBtnCom;
	script->mBtnExit = btExitBtnCom;
	//脚本添加到背景对象，反正有个地方运行就行
	backGround->AddComponent(script);
}
