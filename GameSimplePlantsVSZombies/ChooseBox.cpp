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
	// �˳�����
	Vector2 exitPos = { -233, 344 };
	// �ǳ�����
	Vector2 entryPos = { 233, 344 };

	// ���ѡ����
	GameObject* chooseBoxG = new GameObject("ChooseBox");
	mScene->AddGameObject(chooseBoxG);		//��Ӷ��󵽳���
	chooseBoxG->mTransform->localPosition = exitPos;

	// ����
	GameObject* chooseBoxBgG = new GameObject("chooseBoxBgG");
	mScene->AddGameObject(chooseBoxBgG);		//��Ӷ��󵽳���
	chooseBoxBgG->SetParent(chooseBoxG);
	TextureRender* chooseBoxBgTexC = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath(
		"AdventureScreen/SeedChooser_Background.png"));
	chooseBoxBgG->AddComponent(chooseBoxBgTexC);

	// ����
	GameObject* chooseBoxTitleG = new GameObject("chooseBoxTitleG");
	mScene->AddGameObject(chooseBoxTitleG);		//��Ӷ��󵽳���
	chooseBoxTitleG->SetParent(chooseBoxG);		//���ø�����
	chooseBoxTitleG->mTransform->localPosition = { 0, -240 };
	FontStyle textStyle02;		//������ʽ
	textStyle02.size = 20;
	textStyle02.color = { 255, 213, 159, 43 };
	TextComponent* chooseBoxTitleC = new TextComponent(
		L"ѡ�����ֲ��", textStyle02);
	chooseBoxTitleG->AddComponent(chooseBoxTitleC);		//����ı����

	// ��ť
	GameObject* chooseBoxBtnG = new GameObject("chooseBoxBtnG");
	mScene->AddGameObject(chooseBoxBtnG);
	chooseBoxBtnG->SetParent(chooseBoxG);
	chooseBoxBtnG->mTransform->localPosition = { 0, 190 };
	ImageButton* chooseBoxBtnC = new ImageButton(
		"AdventureScreen/SeedChooser_Button_Disabled.png",
		"AdventureScreen/SeedChooser_Button.png",
		"AdventureScreen/SeedChooser_Button.png");
	chooseBoxBtnG->AddComponent(chooseBoxBtnC);		// ��Ӱ�ť���
	FontStyle textStyle03;	//������ʽ
	textStyle03.size = 20;
	textStyle03.color = { 255, 213, 159, 43 };
	TextComponent* chooseBoxBtnTextC = new TextComponent(
		L"һ��ҡ����", textStyle03);
	chooseBoxBtnG->AddComponent(chooseBoxBtnTextC);	//����ı����

	// ��Ӷ��������������ͽű�ͬ�㣬�����ȡ��
	Animator* bgAnimCom = new Animator();
	chooseBoxG->AddComponent(bgAnimCom);
	// ���ҵǳ�
	bgAnimCom->AddKeyframe("Entry", {
		{0.0f, exitPos},
		{0.5f, entryPos, 0.0f, {1.0f, 1.0f},
			[this, bgAnimCom] {}},
		});
	// �����˳�
	bgAnimCom->AddKeyframe("Exit", {
		{0.0f, entryPos},
		{0.5f, exitPos, 0.0f, {1.0f, 1.0f},
			[this, bgAnimCom] {}},
		});


	// ��ӱ�������
	AudioSource* audio = new AudioSource();
	AddComponent(audio);

	// �ű�
	ChooseBoxScript* script = new ChooseBoxScript();
	script->mStartBtn = chooseBoxBtnC;
	script->mAudio = audio;
	chooseBoxG->AddComponent(script);
}
