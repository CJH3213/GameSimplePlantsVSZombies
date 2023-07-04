#include "LoadingPageScene.h"
#include "Game.h"
#include "MainMenuScene.h"
#include "TextureRender.h"
#include "LoadingSliderPrefab.h"

LoadingPageScene::LoadingPageScene(std::string name):
	SceneBase(name)
{
}

void LoadingPageScene::Start()
{
	//获取窗口大小
	Vector2 windowSize = GetGame()->mWindow->GetSize();

	//加载背景图片
	GameObject* backGround = new GameObject("bgImgO");
	backGround->mTransform->Translate(windowSize / 2, Space::World);	//设置背景图居中在窗口
	AddGameObject(backGround);
	//添加渲染组件
	TextureRender* bgRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("TitleScreen/titlescreen.jpg"));
	backGround->AddComponent(bgRenCom);

	//将slider游戏对象添加进场景
	AddGameObject(new LoadingSlider());
}
