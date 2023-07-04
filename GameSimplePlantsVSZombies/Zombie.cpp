#include "Zombie.h"
#include "SpriteAnimator.h"
#include "Game.h"
#include "ZombieScript.h"
#include "BoxCollider.h"
#include "LifeScript.h"

void Zombie::Instantiate()
{
	mTag = "Zombie";

	// ��Ӿ��鶯��
	SpriteAnimator* spriteAnim = new SpriteAnimator();
	AddComponent(spriteAnim);
	spriteAnim->mDrawOrder = 4;	
	spriteAnim->AddTextures("WalkingGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Zombies/Zombie/WalkingGIF"));
	spriteAnim->AddTextures("ChewingGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Zombies/Zombie/ChewingGIF"));
	spriteAnim->AddTextures("DeathBodyGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Zombies/Zombie/DeathGIF/DeathBodyGIF"));
	// �������߶���
	spriteAnim->SetFPS(5);
	spriteAnim->Play("WalkingGIF");

	// ��ײ��
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 30, 90};
	collider->mOffset = { 20, 25 };

	// �������
	LifeScript* life = new LifeScript();
	AddComponent(life);
	life->SetRange(0, 100);

	// �ű�
	ZombieScript* script = new ZombieScript();
	script->mAnim = spriteAnim;
	script->mCollider = collider;
	AddComponent(script);
}
