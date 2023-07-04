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
	// 退场坐标
	Vector2 exitPos = { 223, -44 };
	// 登场坐标
	Vector2 entryPos = { 223, 43 };

	// 卡片银行
	GameObject* cardBank = new GameObject("CardBank");
	mScene->AddGameObject(cardBank);
	cardBank->mTransform->localPosition = exitPos;
	// 背景图
	TextureRender* cardBankRenCom = new TextureRender(
		GetGame()->mImageManagement->
		GetTextureByPath("AdventureScreen/SeedBank.png"));
	cardBank->AddComponent(cardBankRenCom);

	// 阳光数值
	GameObject* sunNum = new GameObject("SunNum");
	mScene->AddGameObject(sunNum);
	sunNum->SetParent(cardBank);		//卡片银行为父对象
	sunNum->mTransform->localPosition = { -185, 28 };
	// 数值文本
	FontStyle textStyle02;
	textStyle02.size = 20;
	TextComponent* sunNumTextC = new TextComponent(
		std::to_wstring(-123), textStyle02);
	sunNum->AddComponent(sunNumTextC);

	// 添加动作组件（该组件和脚本同层，方便获取）
	Animator* bgAnimCom = new Animator();
	cardBank->AddComponent(bgAnimCom);

	// 脚本
	CardBankScript* script = new CardBankScript();
	script->mSunNumText = sunNumTextC;
	script->mAnimator = bgAnimCom;
	cardBank->AddComponent(script);
}
