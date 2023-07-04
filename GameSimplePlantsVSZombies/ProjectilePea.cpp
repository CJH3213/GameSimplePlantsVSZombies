#include "ProjectilePea.h"
#include "TextureRender.h"
#include "Game.h"
#include "BoxCollider.h"
#include "ProjectilePeaScript.h"

void ProjectilePea::Instantiate()
{
	// 标记为射弹
	mTag = "Projectile";

	// 豌豆图片
	TextureRender* texRen = new TextureRender(GetGame()->
		mImageManagement->GetTextureByPath("AdventureScreen/Peashooter/ProjectilePea.png")
	);
	AddComponent(texRen);

	// 添加碰撞器
	BoxCollider* collider = new BoxCollider();
	AddComponent(collider);
	collider->mSize = { 26, 26 };

	// 添加控制脚本
	ProjectilePeaScript* script = new ProjectilePeaScript();
	AddComponent(script);
}

