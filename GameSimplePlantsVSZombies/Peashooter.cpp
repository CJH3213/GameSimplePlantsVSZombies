#include "Peashooter.h"
#include "SpriteAnimator.h"
#include "Game.h"
#include "BoxCollider.h"
#include "LifeScript.h"
#include "PeashooterScript.h"

void Peashooter::Instantiate()
{
	mName = "Peashooter";
	mTag = "Plant";

	// 添加精灵动画
	SpriteAnimator* anim = new SpriteAnimator();
	AddComponent(anim);
	anim->AddTextures("NormalGIF",
		GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Peashooter/NormalGIF"));
	anim->Play("NormalGIF");

	// 添加碰撞器（自身检测与僵尸相交）
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 50, 60 };

	// 添加生命脚本
	LifeScript* life = new LifeScript();
	AddComponent(life);
	life->SetRange(0, 100);
	life->AddHP(100);

	// 添加控制脚本
	PeashooterScript* script = new PeashooterScript();
	AddComponent(script);
}
