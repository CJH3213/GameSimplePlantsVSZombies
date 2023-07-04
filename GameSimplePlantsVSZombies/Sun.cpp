#include "Sun.h"
#include "SpriteAnimator.h"
#include "Game.h"
#include "Button.h"
#include "SunScript.h"
#include "Animator.h"

void Sun::Instantiate()
{
	// ��Ӿ��鶯��
	SpriteAnimator* spriteAnim = new SpriteAnimator();
	AddComponent(spriteAnim);
	spriteAnim->mDrawOrder = 2;	//����ͼ���ǱȽϿ��ϵ�
	spriteAnim->AddTextures("NormalGIF", GetGame()->mImageManagement->
		GetTexturesByDir("AdventureScreen/Sun/NormalGIF"));
	spriteAnim->Play("NormalGIF");
	// ��Ӱ�ť���
	Button* button = new Button();
	AddComponent(button);
	button->mSize = { 79, 79 };		//��д��̶���ť��С��
	// �˶��������
	Animator* transAnim = new Animator();
	AddComponent(transAnim);
	// ��ӽű�
	SunScript* script = new SunScript();
	AddComponent(script);
	script->mBtn = button;
	script->mAnim = transAnim;
}
