#include "CardScript.h"
#include "GameObject.h"
#include "SceneBase.h"
#include "Animator.h"
#include "TransformComponent.h"
#include "GrowPlant.h"
#include "TextureRender.h"
#include "Game.h"
#include "GrowPlantScript.h"
#include "Time.h"

void CardScript::Awake()
{
	// ��ȡ��Ƭ����
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();
	// ��ȡѡ����
	mChooser = GetScene()->FindGameObject("ChooseBox")->GetComponent<ChooseBoxScript>();
	// ��ȡֲ�������
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// ���ÿ�Ƭ����
	mFace->ChangeTexture(
		GetGame()->mImageManagement->GetTexturesByDir(mCardInfo.resourceFolder)[0]
	);
	// ���ý���ı�
	mCostText->SetContent(std::to_wstring(mCardInfo.amount));

	// ��ӿ�Ƭ����¼�����
	mButton->OnClick.AddListener("CardScript", std::bind(&CardScript::OnClick, this));
	// ������ȴ����ͼԭʼ�ߴ�
	mCDMaskSize = mCDMask->mTexture->GetSize();
	// ������ȴ���ֳ�ʼ״̬Ϊ������
	SetCDMask(0.0f);
	// ���ó�ʼ����״̬Ϊ������
	SetUsable(true);
}

void CardScript::Update()
{
	if (mState >= IsLock)
	{
		if (mCDTime > 0.0f)
		{
			// ��֡���
			float deltaTime = Time::Time_s() - mTimeLast;
			mTimeLast = Time::Time_s();
			// ��ȴʱ�䵹��ʱ
			mCDTime -= deltaTime;
			// �������ֽ���
			float percent = mCDTime / mCardInfo.coolDown;
			SetCDMask(percent);
		}
	}
}

void CardScript::OnClick()
{
	if (mState == IsMoving)
		return;

	// ��Ƭ��ѡ�������������������У����ۣ�
	else if (mState == InChooser)
	{
		AddCard();
	}

	// ��Ƭ�ڿ��ۣ������������Ƴ������ָ�ѡ������ѡ
	else if(mState == InBank)
	{
		RemoveCard();
	}
	
	// ��Ϸ��ʼ�󣬵����Ƭ������ֲ����
	else if (mState == IsLock && mIsUsing)
	{
		if (mPlantManager->mMouseHold == nullptr &&
			mCDTime <= 0.0f)	// ���տա�����û��ȴ���ܱ����
		{
			// ��ȡ����ͼ����
			auto backGround = GetScene()->FindGameObject("BackGround");
			Card* thisCard = dynamic_cast<Card*>(mGameObject);
			// ʵ������ֲ�����
			GrowPlant* obj = new GrowPlant();
			obj->mName = "PreviewPlant";		// ��ʶ������Ϊ��Ԥ��ֲ�
			GetScene()->AddGameObject(obj);
			obj->SetParent(backGround);
			// ����ֲ����Դ��Ϣ
			auto script = obj->GetComponent<GrowPlantScript>();
			script->mPlantInfo.mName = mCardInfo.name;
			script->mPlantInfo.mResourceFolder = mCardInfo.resourceFolder;
			script->mPlantInfo.mPlantPrefab = mCardInfo.plantPrefab;

			// ��ӵ�ֲ�������
			mPlantManager->mMouseHold = obj;
		}
	}
}

void CardScript::SetCDMask(float f)
{
	f = Math::Max(f, 0.0f);
	f = Math::Min(f, 1.0f);

	// ������ȴ���Ƚ�ȡ���ֳ���
	int height = mCDMaskSize.y * f;
	mCDMask->mTexture->rectRgn.h = height;
	// ������
	mCDMask->mOffset.y = (height - mCDMaskSize.y) / 2;
}

void CardScript::AddCard()
{
	// �����Ƿ������Ӹÿ�Ƭ����
	if (mCardBank->IsFull() == false &&
		mCardBank->HasCardWithName(mCardInfo.name) == false)
	{
		// ���ÿ�ƬΪ��ɫ����ʾ�Ѿ�ѡȡ
		SetUsable(false);

		// ���𶯻��Ŀ�Ƭ
		Card* newCard = new Card();
		GetScene()->AddGameObject(newCard);
		newCard->SetParent(mCardBank->GetGameObject());	// �������¿�Ƭ�ĸ�����

		auto newCardScript = newCard->GetComponent<CardScript>();
		// ���ƿ�����Ϣ
		newCardScript->mCardInfo = mCardInfo;
		// ��ע�ÿ�Ƭ���������Ŷ�����
		newCardScript->mState = CardScript::IsMoving;

		// ��ȡ��ƬӦ�õ��￨�۵�����
		int index = mCardBank->GetCardCount();
		Vector2 pos = mCardBank->GetCardCenterPos(index);
		// ����Ƭ��ӵ�����
		mCardBank->AddCard(newCard);

		// ��Ӷ������
		Animator* animCom = new Animator();
		newCard->AddComponent(animCom);
		animCom->AddKeyframe("ToBank", {	//���ֿ�Ƭλ���ƶ�������
			{0.0f, GetTransform()->GetPosition()},
			{0.2f, pos, 0.0f, {1.0f, 1.0f}, [this, newCardScript]	// ����ʱ�価���죬������һ��Сbug
			{newCardScript->mState = CardScript::InBank; }},
			});
		animCom->Play("ToBank");
	}
}

void CardScript::RemoveCard()
{

	Card* thisCard = dynamic_cast<Card*>(mGameObject);

	// �ӿ�Ƭ�������ٿ�Ƭ
	mCardBank->RemoveCard(mCardInfo.name);
	// �ָ�ѡ������ƬЧ��
	mChooser->GiveBack(mCardInfo.name);

	// ���ٶ�������
	DestroyAllChildren(thisCard);
	Destroy(thisCard);
}

void CardScript::BeginCoolDown()
{
	mCDTime = mCardInfo.coolDown;
	mTimeLast = Time::Time_s();
}

void CardScript::SetUsable(bool b)
{
	mIsUsing = b;

	mDisableMask->SetEnable(!b);
}

