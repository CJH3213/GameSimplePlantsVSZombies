#include "SunScript.h"
#include "SceneBase.h"
#include "Time.h"

void SunScript::ToBankFinish()
{
	// 先假设一个阳光值50
	mCardBank->AddSunNum(50);

	// 阳光到达目的地咯，销毁阳光图案
	Destroy(mGameObject);
}

void SunScript::OnClick()
{
	// 点击后就不能自动销毁了，加一个大数让动画播放完毕
	mDisappearTime += 10.0f;

	// 卡片银行“太阳”图标位置
	Vector2 sunEndPos = mCardBank->GetTransform()->GetPosition() - Vector2(182.0f, 8.0f);
	// 添加运动动画
	mAnim->AddKeyframe("ToBank", {
		{0.0f, mGameObject->mTransform->GetPosition(), 0.0f, GetTransform()->localScale},
		{0.8f, sunEndPos, 0.0f, GetTransform()->localScale,
			[this] {mCardBank->AddSunNum(mIsBigSun ? 50 : 25); }},
		{1.3f, sunEndPos, 0.0f, GetTransform()->localScale * Vector2{0.3f, 0.3f},
			[this] {Destroy(mGameObject); }}
		});
	mAnim->Play("ToBank");
	mBtn->SetEnable(false);
}

void SunScript::Awake()
{
	// 计算阳光消失时间=当前时间之后的8秒
	mDisappearTime = Time::Time_s() + 8.0f;

	// 根据太阳大小设置角色大小
	//if (mIsBigSun)
	//{
	//	GetTransform()->localScale = { 1.0f, 1.0f };
	//}
	//else
	//{
	//	GetTransform()->localScale = { 0.6f, 0.6f };
	//}
	//mBtn->mSize *= GetTransform()->localScale;

	// 获取卡片银行脚本
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();

	// 添加点击事件回调
	mBtn->OnClick.AddListener("OnClick", std::bind(&SunScript::OnClick, this));
}

void SunScript::Update()
{
	if (Time::Time_s() >= mDisappearTime)
	{
		Destroy(mGameObject);
	}
}

void SunScript::SetIsBigSun(bool b)
{
	mIsBigSun = b;
	// 设置图形缩放大小
	if (mIsBigSun)
	{
		GetTransform()->localScale = { 1.0f, 1.0f };
	}
	else
	{
		GetTransform()->localScale = { 0.6f, 0.6f };
	}
	mBtn->mSize *= GetTransform()->localScale;
}
