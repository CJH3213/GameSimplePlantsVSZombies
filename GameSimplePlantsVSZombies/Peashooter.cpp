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

	// ��Ӿ��鶯��
	SpriteAnimator* anim = new SpriteAnimator();
	AddComponent(anim);
	anim->AddTextures("NormalGIF",
		GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Peashooter/NormalGIF"));
	anim->Play("NormalGIF");

	// �����ײ�����������뽩ʬ�ཻ��
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 50, 60 };

	// ��������ű�
	LifeScript* life = new LifeScript();
	AddComponent(life);
	life->SetRange(0, 100);
	life->AddHP(100);

	// ��ӿ��ƽű�
	PeashooterScript* script = new PeashooterScript();
	AddComponent(script);
}
