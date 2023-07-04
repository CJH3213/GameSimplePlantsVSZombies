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
	// 获取卡片银行
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();
	// 获取选卡栏
	mChooser = GetScene()->FindGameObject("ChooseBox")->GetComponent<ChooseBoxScript>();
	// 获取植物管理器
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// 设置卡片纹理
	mFace->ChangeTexture(
		GetGame()->mImageManagement->GetTexturesByDir(mCardInfo.resourceFolder)[0]
	);
	// 设置金额文本
	mCostText->SetContent(std::to_wstring(mCardInfo.amount));

	// 添加卡片点击事件监听
	mButton->OnClick.AddListener("CardScript", std::bind(&CardScript::OnClick, this));
	// 保存冷却遮罩图原始尺寸
	mCDMaskSize = mCDMask->mTexture->GetSize();
	// 设置冷却遮罩初始状态为无遮罩
	SetCDMask(0.0f);
	// 设置初始禁用状态为无遮罩
	SetUsable(true);
}

void CardScript::Update()
{
	if (mState >= IsLock)
	{
		if (mCDTime > 0.0f)
		{
			// 两帧间隔
			float deltaTime = Time::Time_s() - mTimeLast;
			mTimeLast = Time::Time_s();
			// 冷却时间倒计时
			mCDTime -= deltaTime;
			// 设置遮罩进度
			float percent = mCDTime / mCardInfo.coolDown;
			SetCDMask(percent);
		}
	}
}

void CardScript::OnClick()
{
	if (mState == IsMoving)
		return;

	// 卡片在选卡栏，点击后添加至银行（卡槽）
	else if (mState == InChooser)
	{
		AddCard();
	}

	// 卡片在卡槽，点击后从银行移除，并恢复选卡栏可选
	else if(mState == InBank)
	{
		RemoveCard();
	}
	
	// 游戏开始后，点击卡片生成种植对象
	else if (mState == IsLock && mIsUsing)
	{
		if (mPlantManager->mMouseHold == nullptr &&
			mCDTime <= 0.0f)	// 鼠标空空、卡牌没冷却才能被点击
		{
			// 获取背景图对象
			auto backGround = GetScene()->FindGameObject("BackGround");
			Card* thisCard = dynamic_cast<Card*>(mGameObject);
			// 实例化种植物对象
			GrowPlant* obj = new GrowPlant();
			obj->mName = "PreviewPlant";		// 标识对象名为“预览植物”
			GetScene()->AddGameObject(obj);
			obj->SetParent(backGround);
			// 传入植物资源信息
			auto script = obj->GetComponent<GrowPlantScript>();
			script->mPlantInfo.mName = mCardInfo.name;
			script->mPlantInfo.mResourceFolder = mCardInfo.resourceFolder;
			script->mPlantInfo.mPlantPrefab = mCardInfo.plantPrefab;

			// 添加到植物管理器
			mPlantManager->mMouseHold = obj;
		}
	}
}

void CardScript::SetCDMask(float f)
{
	f = Math::Max(f, 0.0f);
	f = Math::Min(f, 1.0f);

	// 根据冷却进度截取遮罩长度
	int height = mCDMaskSize.y * f;
	mCDMask->mTexture->rectRgn.h = height;
	// 顶对齐
	mCDMask->mOffset.y = (height - mCDMaskSize.y) / 2;
}

void CardScript::AddCard()
{
	// 卡槽是否符合添加该卡片条件
	if (mCardBank->IsFull() == false &&
		mCardBank->HasCardWithName(mCardInfo.name) == false)
	{
		// 设置卡片为黑色，提示已经选取
		SetUsable(false);

		// 负责动画的卡片
		Card* newCard = new Card();
		GetScene()->AddGameObject(newCard);
		newCard->SetParent(mCardBank->GetGameObject());	// 卡槽是新卡片的父对象

		auto newCardScript = newCard->GetComponent<CardScript>();
		// 复制卡面信息
		newCardScript->mCardInfo = mCardInfo;
		// 标注该卡片就是用来放动画的
		newCardScript->mState = CardScript::IsMoving;

		// 获取卡片应该到达卡槽的坐标
		int index = mCardBank->GetCardCount();
		Vector2 pos = mCardBank->GetCardCenterPos(index);
		// 将卡片添加到卡槽
		mCardBank->AddCard(newCard);

		// 添加动作组件
		Animator* animCom = new Animator();
		newCard->AddComponent(animCom);
		animCom->AddKeyframe("ToBank", {	//从现卡片位置移动到卡槽
			{0.0f, GetTransform()->GetPosition()},
			{0.2f, pos, 0.0f, {1.0f, 1.0f}, [this, newCardScript]	// 动画时间尽量快，否则有一个小bug
			{newCardScript->mState = CardScript::InBank; }},
			});
		animCom->Play("ToBank");
	}
}

void CardScript::RemoveCard()
{

	Card* thisCard = dynamic_cast<Card*>(mGameObject);

	// 从卡片银行销毁卡片
	mCardBank->RemoveCard(mCardInfo.name);
	// 恢复选卡栏卡片效果
	mChooser->GiveBack(mCardInfo.name);

	// 销毁对象申请
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

