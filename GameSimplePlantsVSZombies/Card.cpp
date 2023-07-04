#include "Card.h"
#include "FontManager.h"
#include "CardScript.h"
#include "TextureRender.h"
#include "TextComponent.h"
#include "SceneBase.h"
#include "Button.h"
#include "Game.h"

void Card::Instantiate()
{
	/*
	原版游戏素材卡片底图就是两倍大小，显示时需要缩小一半大小，
	只要将植物也缩小一倍，刚好可以作为头像的大小。
	*/


	// 卡片底图
	GameObject* cardBackGround = new GameObject("CardBackGround");
	mScene->AddGameObject(cardBackGround);
	cardBackGround->SetParent(this);		//卡片银行为父对象
	cardBackGround->mTransform->localScale = { 0.5, 0.5 };
	// 图
	TextureRender* cardBGRenC = new TextureRender(
		mScene->GetGame()->mImageManagement->GetTextureByPath(
			"AdventureScreen/SeedPacket_Larger.png"
		));
	cardBackGround->AddComponent(cardBGRenC);
	// 按钮组件
	Button* cardBtnCom = new Button();
	cardBackGround->AddComponent(cardBtnCom);
	cardBtnCom->mSize = cardBGRenC->mTexture->GetSize() * 
		cardBackGround->mTransform->GetScale();

	// 卡片头像图
	GameObject* cardFace = new GameObject("CardFace");
	mScene->AddGameObject(cardFace);
	cardFace->SetParent(cardBackGround);		//卡片底图为父对象
	cardFace->mTransform->localPosition = { 0, -5 };
	// 证件照
	TextureRender* faceRenCom = new TextureRender(nullptr);
	cardFace->AddComponent(faceRenCom);

	// 卡片金额
	GameObject* priceNum = new GameObject("PriceNum");
	mScene->AddGameObject(priceNum);
	priceNum->SetParent(cardBackGround);		//卡片底图为父对象
	priceNum->mTransform->localPosition = { -5, 26 };
	// 数值文本
	FontStyle textStyle03;
	textStyle03.size = 22;
	textStyle03.glyph = Bold;
	TextComponent* priceNumTextC = new TextComponent(L"-1", textStyle03);
	priceNum->AddComponent(priceNumTextC);

	// 不可使用遮罩（比如余额不足、植物不能在本关卡使用等）
	GameObject* disableMaskG = new GameObject("DisableMask");
	mScene->AddGameObject(disableMaskG);
	disableMaskG->SetParent(cardBackGround);		//卡片底图为父对象
	TextureRender* disableMaskRenCom = new TextureRender(
		GetGame()->mImageManagement->GetTextureByPath(
			"AdventureScreen/SeedPacket_Mask.png"));
	disableMaskG->AddComponent(disableMaskRenCom);

	// 冷却进度遮罩
	GameObject* cdMaskG = new GameObject("CDMask");
	mScene->AddGameObject(cdMaskG);
	cdMaskG->SetParent(cardBackGround);		//卡片底图为父对象
	TextureRender* cdMaskRenCom = new TextureRender(
		GetGame()->mImageManagement->GetTextureByPath(
			"AdventureScreen/SeedPacket_Mask.png"));
	cdMaskG->AddComponent(cdMaskRenCom);

	// 脚本
	CardScript* cardScript = new CardScript();
	cardScript->mButton = cardBtnCom;		// 依赖注入组件，也可以动态Get…
	cardScript->mFace = faceRenCom;
	cardScript->mCostText = priceNumTextC;
	cardScript->mDisableMask = disableMaskRenCom;
	cardScript->mCDMask = cdMaskRenCom;
	this->AddComponent(cardScript);		//脚本挂预制件上

}
