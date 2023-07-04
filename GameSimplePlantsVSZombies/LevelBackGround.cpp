#include "LevelBackGround.h"
#include "SceneBase.h"
#include "Game.h"
#include "TextureRender.h"
#include "Animator.h"
#include "LevelBackGroundScript.h"

void LevelBackGround::Instantiate()
{
	// 获取窗口大小
	Vector2 windowSize = GetScene()->GetGame()->mWindow->GetSize();

	// 加载背景图片
	GameObject* backGround = new GameObject("BackGround");
	mScene->AddGameObject(backGround);
	backGround->mTransform->localPosition = { 700, windowSize.y / 2 };	  // 设置背景左对齐
	// 添加渲染组件
	TextureRender* bgRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/background1.jpg"));
	backGround->AddComponent(bgRenCom);
	// 添加动作组件
	Animator* bgAnimCom = new Animator();
	backGround->AddComponent(bgAnimCom);

	// 控制脚本
	LevelBackGroundScript* script = new LevelBackGroundScript();
	backGround->AddComponent(script);
}
