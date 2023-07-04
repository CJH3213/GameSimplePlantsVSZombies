#include "ProjectilePea.h"
#include "TextureRender.h"
#include "Game.h"
#include "BoxCollider.h"
#include "ProjectilePeaScript.h"

void ProjectilePea::Instantiate()
{
	// ���Ϊ�䵯
	mTag = "Projectile";

	// �㶹ͼƬ
	TextureRender* texRen = new TextureRender(GetGame()->
		mImageManagement->GetTextureByPath("AdventureScreen/Peashooter/ProjectilePea.png")
	);
	AddComponent(texRen);

	// �����ײ��
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 26, 26 };

	// ��ӿ��ƽű�
	ProjectilePeaScript* script = new ProjectilePeaScript();
	AddComponent(script);
}

