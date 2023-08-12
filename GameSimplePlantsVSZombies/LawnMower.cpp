#include "LawnMower.h"
#include "TextureRender.h"
#include "Game.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "LawnMowerScript.h"

void LawnMower::Instantiate()
{
	mTag = "LawnMower";

	// 背景图
	TextureRender* cardBankRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/LawnMower.png"));
	AddComponent(cardBankRenCom);

	// 添加碰撞器组件
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 20, 60 };
	collider->mOffset.x = 20;
	//collider->SetEnable(false);

	// 动作组件
	Animator* anim = new Animator();
	AddComponent(anim);

	// 添加控制脚本
	LawnMowerScript* script = new LawnMowerScript();
	AddComponent(script);
	script->mCollider = collider;
	script->mAnim = anim;
}
