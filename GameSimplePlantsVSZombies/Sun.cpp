#include "Sun.h"
#include "SpriteAnimator.h"
#include "Game.h"
#include "Button.h"
#include "SunScript.h"
#include "Animator.h"

void Sun::Instantiate()
{
	// 添加精灵动画
	SpriteAnimator* spriteAnim = new SpriteAnimator();
	AddComponent(spriteAnim);
	spriteAnim->mDrawOrder = 2;	//阳光图层是比较靠上的
	spriteAnim->AddTextures("NormalGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Sun/NormalGIF"));
	spriteAnim->Play("NormalGIF");
	// 添加按钮组件
	Button* button = new Button();
	AddComponent(button);
	button->mSize = { 79, 79 };		//先写入固定按钮大小吧
	// 运动动画组件
	Animator* transAnim = new Animator();
	AddComponent(transAnim);
	// 添加脚本
	SunScript* script = new SunScript();
	AddComponent(script);
	script->mBtn = button;
	script->mAnim = transAnim;
}
