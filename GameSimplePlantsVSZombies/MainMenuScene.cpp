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
	// ��ȡ���ڴ�С
	Vector2 windowSize = GetGame()->mWindow->GetSize();

	// ���ر���ͼƬ
	GameObject* backGround = new GameObject("bgImgO");
	backGround->mTransform->Translate(windowSize / 2, Space::World);	//���ñ���ͼ�����ڴ���
	AddGameObject(backGround);
	// �����Ⱦ���
	TextureRender* bgRenCom = new TextureRender(
		GetGame()->mImageManagement->GetTextureByPath(
		"SelectorScreen/Surface.png"));
	backGround->AddComponent(bgRenCom);

	// ���ؿ�ʼð�հ�ť
	GameObject* btStarAdventure = new GameObject("StarAdventureG");
	btStarAdventure->SetParent(backGround);	//����ͼΪ��ť�ĸ�����
	btStarAdventure->mTransform->localPosition = Vector2(170, -160);
	AddGameObject(btStarAdventure);
	// ��Ӱ�ť���
	GraveButton* btStartBtnCom = new GraveButton(
		"SelectorScreen/SelectorScreen_StartAdventure_Button1.png",
		"SelectorScreen/SelectorScreen_StartAdventure_Highlight.png");
	btStarAdventure->AddComponent(btStartBtnCom);

	// �˳���ť
	GameObject* btExit = new GameObject("ExitG");
	btExit->SetParent(backGround);	//����ͼΪ��ť�ĸ�����
	btExit->mTransform->localPosition = Vector2(345, 225);
	AddGameObject(btExit);
	// ������ְ�ť���
	FontStyle textSty01;
	textSty01.size = 23;
	FontStyle textSty02;
	textSty02.size = 30;
	textSty02.color = Color::Green;
	TextButton* btExitBtnCom = new TextButton(
		L"�˳�", textSty01, textSty02);
	btExit->AddComponent(btExitBtnCom);

	// �ű�02
	Script02* script = new Script02();
	script->mBtnStart = btStartBtnCom;
	script->mBtnExit = btExitBtnCom;
	//�ű���ӵ��������󣬷����и��ط����о���
	backGround->AddComponent(script);
}
