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
	场景初始化说明：
	1. 场景初始化即实例化游戏对象、组件，并把它们关联起来，设置初始值的作用；
	2. 此时组件并未初始化，组件的成员只能设置初值，不能获取，以防引用到空指针；
	3. tansform是特殊组件，在游戏对象实例化时存在，可以设置和获取该组件的值；
	4. 各种环境参数，如Game对象及其子成员、场景对象，都是可以获得的；
	*/

	// 获取窗口大小
	Vector2 windowSize = GetGame()->mWindow->GetSize();

	// 添加关卡背景图
	AddGameObject(new LevelBackGround());

	// 加载菜单按钮
	GameObject* btMenuG = new GameObject("BtnMenuG");
	AddGameObject(btMenuG);
	// 添加按钮组件
	ImageButton* btMenuBtnCom = new ImageButton(
		"AdventureScreen/button.png", "AdventureScreen/button.png",
		"AdventureScreen/button_down.png");
	btMenuG->AddComponent(btMenuBtnCom);
	//添加文本组件
	FontStyle textStyle01;
	textStyle01.size = 20;
	textStyle01.color = Color::Green;
	TextComponent* btMenuTextCom = new TextComponent(L"菜单", textStyle01);
	btMenuG->AddComponent(btMenuTextCom);
	// 设置按钮位置
	btMenuG->mTransform->localPosition = { 741, 22};

	// 添加卡片银行
	AddGameObject(new CardBank());

	// 添加选卡栏
	AddGameObject(new ChooseBox());

	// 角色管理器
	AddGameObject(new LevelManager());

}
