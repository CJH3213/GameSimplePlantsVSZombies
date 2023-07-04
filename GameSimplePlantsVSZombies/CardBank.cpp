#include "CardBank.h"
#include "TextureRender.h"
#include "TextComponent.h"
#include "Card.h"
#include "SceneBase.h"
#include "CardBankScript.h"
#include "Animator.h"
#include "Game.h"

void CardBank::Instantiate()
{
	// �˳�����
	Vector2 exitPos = { 223, -44 };
	// �ǳ�����
	Vector2 entryPos = { 223, 43 };

	// ��Ƭ����
	GameObject* cardBank = new GameObject("CardBank");
	mScene->AddGameObject(cardBank);
	cardBank->mTransform->localPosition = exitPos;
	// ����ͼ
	TextureRender* cardBankRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/SeedBank.png"));
	cardBank->AddComponent(cardBankRenCom);

	// ������ֵ
	GameObject* sunNum = new GameObject("SunNum");
	mScene->AddGameObject(sunNum);
	sunNum->SetParent(cardBank);		//��Ƭ����Ϊ������
	sunNum->mTransform->localPosition = { -185, 28 };
	// ��ֵ�ı�
	FontStyle textStyle02;
	textStyle02.size = 20;
	TextComponent* sunNumTextC = new TextComponent(
		std::to_wstring(-123), textStyle02);
	sunNum->AddComponent(sunNumTextC);

	// ��Ӷ��������������ͽű�ͬ�㣬�����ȡ��
	Animator* bgAnimCom = new Animator();
	cardBank->AddComponent(bgAnimCom);

	// �ű�
	CardBankScript* script = new CardBankScript();
	script->mSunNumText = sunNumTextC;
	script->mAnimator = bgAnimCom;
	cardBank->AddComponent(script);
}
