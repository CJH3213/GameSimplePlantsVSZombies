#include "Zombie.h"
#include "SpriteAnimator.h"
#include "Game.h"
#include "ZombieScript.h"
#include "BoxCollider.h"
#include "LifeScript.h"

void Zombie::Instantiate()
{
	mTag = "Zombie";

	// 添加精灵动画
	SpriteAnimator* spriteAnim = new SpriteAnimator();
	AddComponent(spriteAnim);
	spriteAnim->mDrawOrder = 4;	
	spriteAnim->AddTextures("WalkingGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Zombies/Zombie/WalkingGIF"));
	spriteAnim->AddTextures("ChewingGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Zombies/Zombie/ChewingGIF"));
	spriteAnim->AddTextures("DeathBodyGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Zombies/Zombie/DeathGIF/DeathBodyGIF"));
	// 播放行走动画
	spriteAnim->SetFPS(5);
	spriteAnim->Play("WalkingGIF");

	// 碰撞器
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 30, 90};
	collider->mOffset = { 20, 25 };

	// 生命组件
	LifeScript* life = new LifeScript();
	AddComponent(life);
	life->SetRange(0, 100);

	// 脚本
	ZombieScript* script = new ZombieScript();
	script->mAnim = spriteAnim;
	script->mCollider = collider;
	AddComponent(script);
}
