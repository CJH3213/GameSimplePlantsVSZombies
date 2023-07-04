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
	//��ȡ���ڴ�С
	Vector2 windowSize = GetGame()->mWindow->GetSize();

	//���ر���ͼƬ
	GameObject* backGround = new GameObject("bgImgO");
	backGround->mTransform->Translate(windowSize / 2, Space::World);	//���ñ���ͼ�����ڴ���
	AddGameObject(backGround);
	//�����Ⱦ���
	TextureRender* bgRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("TitleScreen/titlescreen.jpg"));
	backGround->AddComponent(bgRenCom);

	//��slider��Ϸ������ӽ�����
	AddGameObject(new LoadingSlider());
}
