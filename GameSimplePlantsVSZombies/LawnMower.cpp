#include "LawnMower.h"
#include "TextureRender.h"
#include "Game.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "LawnMowerScript.h"

void LawnMower::Instantiate()
{
	mTag = "LawnMower";

	// ����ͼ
	TextureRender* cardBankRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/LawnMower.png"));
	AddComponent(cardBankRenCom);

	// �����ײ�����
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 20, 60 };
	collider->mOffset.x = 20;
	//collider->SetEnable(false);

	// �������
	Animator* anim = new Animator();
	AddComponent(anim);

	// ��ӿ��ƽű�
	LawnMowerScript* script = new LawnMowerScript();
	AddComponent(script);
	script->mCollider = collider;
	script->mAnim = anim;
}
