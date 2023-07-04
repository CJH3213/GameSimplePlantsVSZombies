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

	// ��Ӿ��鶯��
	SpriteAnimator* anim = new SpriteAnimator();
	AddComponent(anim);
	anim->AddTextures("NormalGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Sunflower/NormalGIF"));
	anim->Play("NormalGIF");

	// �����ײ�����
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 50, 60 };

	// ��������ű�
	LifeScript* life = new LifeScript();
	AddComponent(life);
	life->SetRange(0, 100);
	life->AddHP(100);

	// ��ӽű�
	SunflowerScript* script = new SunflowerScript();
	AddComponent(script);
}
