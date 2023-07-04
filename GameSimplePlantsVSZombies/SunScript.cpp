#include "SunScript.h"
#include "SceneBase.h"
#include "Time.h"

void SunScript::ToBankFinish()
{
	// �ȼ���һ������ֵ50
	mCardBank->AddSunNum(50);

	// ���⵽��Ŀ�ĵؿ�����������ͼ��
	Destroy(mGameObject);
}

void SunScript::OnClick()
{
	// �����Ͳ����Զ������ˣ���һ�������ö����������
	mDisappearTime += 10.0f;

	// ��Ƭ���С�̫����ͼ��λ��
	Vector2 sunEndPos = mCardBank->GetTransform()->GetPosition() - Vector2(182.0f, 8.0f);
	// ����˶�����
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
	// ����������ʧʱ��=��ǰʱ��֮���8��
	mDisappearTime = Time::Time_s() + 8.0f;

	// ����̫����С���ý�ɫ��С
	//if (mIsBigSun)
	//{
	//	GetTransform()->localScale = { 1.0f, 1.0f };
	//}
	//else
	//{
	//	GetTransform()->localScale = { 0.6f, 0.6f };
	//}
	//mBtn->mSize *= GetTransform()->localScale;

	// ��ȡ��Ƭ���нű�
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();

	// ��ӵ���¼��ص�
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
	// ����ͼ�����Ŵ�С
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
