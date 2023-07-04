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
	ԭ����Ϸ�زĿ�Ƭ��ͼ����������С����ʾʱ��Ҫ��Сһ���С��
	ֻҪ��ֲ��Ҳ��Сһ�����պÿ�����Ϊͷ��Ĵ�С��
	*/


	// ��Ƭ��ͼ
	GameObject* cardBackGround = new GameObject("CardBackGround");
	mScene->AddGameObject(cardBackGround);
	cardBackGround->SetParent(this);		//��Ƭ����Ϊ������
	cardBackGround->mTransform->localScale = { 0.5, 0.5 };
	// ͼ
	TextureRender* cardBGRenC = new TextureRender(
		mScene->GetGame()->mImageManagement->GetTextureByPath(
			"AdventureScreen/SeedPacket_Larger.png"
		));
	cardBackGround->AddComponent(cardBGRenC);
	// ��ť���
	Button* cardBtnCom = new Button();
	cardBackGround->AddComponent(cardBtnCom);
	cardBtnCom->mSize = cardBGRenC->mTexture->GetSize() * 
		cardBackGround->mTransform->GetScale();

	// ��Ƭͷ��ͼ
	GameObject* cardFace = new GameObject("CardFace");
	mScene->AddGameObject(cardFace);
	cardFace->SetParent(cardBackGround);		//��Ƭ��ͼΪ������
	cardFace->mTransform->localPosition = { 0, -5 };
	// ֤����
	TextureRender* faceRenCom = new TextureRender(nullptr);
	cardFace->AddComponent(faceRenCom);

	// ��Ƭ���
	GameObject* priceNum = new GameObject("PriceNum");
	mScene->AddGameObject(priceNum);
	priceNum->SetParent(cardBackGround);		//��Ƭ��ͼΪ������
	priceNum->mTransform->localPosition = { -5, 26 };
	// ��ֵ�ı�
	FontStyle textStyle03;
	textStyle03.size = 22;
	textStyle03.glyph = Bold;
	TextComponent* priceNumTextC = new TextComponent(L"-1", textStyle03);
	priceNum->AddComponent(priceNumTextC);

	// ����ʹ�����֣��������㡢ֲ�ﲻ���ڱ��ؿ�ʹ�õȣ�
	GameObject* disableMaskG = new GameObject("DisableMask");
	mScene->AddGameObject(disableMaskG);
	disableMaskG->SetParent(cardBackGround);		//��Ƭ��ͼΪ������
	TextureRender* disableMaskRenCom = new TextureRender(
		GetGame()->mImageManagement->GetTextureByPath(
			"AdventureScreen/SeedPacket_Mask.png"));
	disableMaskG->AddComponent(disableMaskRenCom);

	// ��ȴ��������
	GameObject* cdMaskG = new GameObject("CDMask");
	mScene->AddGameObject(cdMaskG);
	cdMaskG->SetParent(cardBackGround);		//��Ƭ��ͼΪ������
	TextureRender* cdMaskRenCom = new TextureRender(
		GetGame()->mImageManagement->GetTextureByPath(
			"AdventureScreen/SeedPacket_Mask.png"));
	cdMaskG->AddComponent(cdMaskRenCom);

	// �ű�
	CardScript* cardScript = new CardScript();
	cardScript->mButton = cardBtnCom;		// ����ע�������Ҳ���Զ�̬Get��
	cardScript->mFace = faceRenCom;
	cardScript->mCostText = priceNumTextC;
	cardScript->mDisableMask = disableMaskRenCom;
	cardScript->mCDMask = cdMaskRenCom;
	this->AddComponent(cardScript);		//�ű���Ԥ�Ƽ���

}
