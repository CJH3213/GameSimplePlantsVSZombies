#include "AdventurePage.h"
#include "Game.h"
#include "TextureRender.h"
#include "ImageButton.h"
#include "TextComponent.h"
#include "LevelBackGround.h"
#include "CardBank.h"
#include "Animator.h"
#include "ChooseBox.h"
#include "LevelManager.h"

AdventurePage::AdventurePage(std::string name)
	: SceneBase(name)
{
}

void AdventurePage::Start()
{
	/*
	������ʼ��˵����
	1. ������ʼ����ʵ������Ϸ����������������ǹ������������ó�ʼֵ�����ã�
	2. ��ʱ�����δ��ʼ��������ĳ�Աֻ�����ó�ֵ�����ܻ�ȡ���Է����õ���ָ�룻
	3. tansform���������������Ϸ����ʵ����ʱ���ڣ��������úͻ�ȡ�������ֵ��
	4. ���ֻ�����������Game�������ӳ�Ա���������󣬶��ǿ��Ի�õģ�
	*/

	// ��ȡ���ڴ�С
	Vector2 windowSize = GetGame()->mWindow->GetSize();

	// ��ӹؿ�����ͼ
	AddGameObject(new LevelBackGround());

	// ���ز˵���ť
	GameObject* btMenuG = new GameObject("BtnMenuG");
	AddGameObject(btMenuG);
	// ��Ӱ�ť���
	ImageButton* btMenuBtnCom = new ImageButton(
		"AdventureScreen/button.png", "AdventureScreen/button.png",
		"AdventureScreen/button_down.png");
	btMenuG->AddComponent(btMenuBtnCom);
	//����ı����
	FontStyle textStyle01;
	textStyle01.size = 20;
	textStyle01.color = Color::Green;
	TextComponent* btMenuTextCom = new TextComponent(L"�˵�", textStyle01);
	btMenuG->AddComponent(btMenuTextCom);
	// ���ð�ťλ��
	btMenuG->mTransform->localPosition = { 741, 22};

	// ��ӿ�Ƭ����
	AddGameObject(new CardBank());

	// ���ѡ����
	AddGameObject(new ChooseBox());

	// ��ɫ������
	AddGameObject(new LevelManager());

}
