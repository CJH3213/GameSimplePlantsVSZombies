#include "LevelBackGround.h"
#include "SceneBase.h"
#include "Game.h"
#include "TextureRender.h"
#include "Animator.h"
#include "LevelBackGroundScript.h"

void LevelBackGround::Instantiate()
{
	// ��ȡ���ڴ�С
	Vector2 windowSize = GetScene()->GetGame()->mWindow->GetSize();

	// ���ر���ͼƬ
	GameObject* backGround = new GameObject("BackGround");
	mScene->AddGameObject(backGround);
	backGround->mTransform->localPosition = { 700, windowSize.y / 2 };	  // ���ñ��������
	// �����Ⱦ���
	TextureRender* bgRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/background1.jpg"));
	backGround->AddComponent(bgRenCom);
	// ��Ӷ������
	Animator* bgAnimCom = new Animator();
	backGround->AddComponent(bgAnimCom);

	// ���ƽű�
	LevelBackGroundScript* script = new LevelBackGroundScript();
	backGround->AddComponent(script);
}
