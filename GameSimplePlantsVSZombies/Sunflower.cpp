#include "Sunflower.h"
#include "SpriteAnimator.h"
#include "Game.h"
#include "SunflowerScript.h"
#include "BoxCollider.h"
#include "LifeScript.h"

void Sunflower::Instantiate()
{
	mName = "Sunflower";
	mTag = "Plant";

	// 添加精灵动画
	SpriteAnimator* anim = new SpriteAnimator();
	AddComponent(anim);
	anim->AddTextures("NormalGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Sunflower/NormalGIF"));
	anim->Play("NormalGIF");

	// 添加碰撞器组件
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 50, 60 };

	// 添加生命脚本
	LifeScript* life = new LifeScript();
	AddComponent(life);
	life->SetRange(0, 100);
	life->AddHP(100);

	// 添加脚本
	SunflowerScript* script = new SunflowerScript();
	AddComponent(script);
}
