#include "ZombieScript.h"
#include "TransformComponent.h"
#include "Time.h"
#include "SceneBase.h"
#include "TurfScript.h"
using namespace std::placeholders;

bool ZombieScript::IsCollisionWithPlant()
{
	for (auto& other : mCollider->GetCollisionState())
		if (other.first->GetGameObj()->mTag == "Plant")
			return true;
	return false;
}

void ZombieScript::ToWalking()
{
	mWalkingSpeed = 12;
	mAnim->Play("WalkingGIF");
	mPlantLife = nullptr;
}

void ZombieScript::Awake()
{
	// ע����ײ�����¼�
	mCollider->mEnterEvents.AddListener("Enter", std::bind(&ZombieScript::CollisionEnter, this, _1));
	mCollider->mStayEvents.AddListener("Stay", std::bind(&ZombieScript::CollisionStay, this, _1));
	//mCollider->mExitEvents.AddListener("Exit", std::bind(&ZombieScript::CollisionExit, this, _1));

	// ��������ֵ�仯�¼�
	mGameObject->GetComponent<LifeScript>()->mChangeEvents.
		AddListener("HPChange", std::bind(&ZombieScript::HPChange, this, _1));

	// У��y����
	GetTransform()->localPosition.y -= 25;

	mLastTime = Time::Time_s();
}

void ZombieScript::Update()
{
	// ������֡���ʱ��
	float deltaTime = Time::Time_s() - mLastTime;
	mLastTime = Time::Time_s();

	// ��ʬ�����ƶ�
	//mWalkingSpeed = 12;
	GetTransform()->localPosition.x -= deltaTime * mWalkingSpeed;
	if(GetTransform()->GetPosition().x < 0)
		GetTransform()->localPosition.x = 290;

	// ����ֲ���ֲ��ֱ�����٣��Ȳ��ǿ�ѪҲ������ײ����
	// �ڲ���ͨ���㲥�ķ�ʽ����£�Ŀǰֻ��ͨ���ж���ײ���Ƿ���ֲ��
	// ���û�к�ֲ����ײ�ˣ��ͻָ����߶���
	if (mPlantLife != nullptr && mCollider->IsEnable() == true &&
		IsCollisionWithPlant() == false)
		ToWalking();

}

void ZombieScript::CollisionEnter(ICollider* other)
{
	if (other->GetGameObj()->mTag == "Plant"
		&& mPlantLife == nullptr)	// ������ڳ�ֲ���Ҳ��������ˣ���Ҫ���Ҳ�ֲ��
	{
		mWalkingSpeed = 0;
		mAnim->Play("ChewingGIF");

		mPlantLife = other->GetGameObj()->GetComponent<LifeScript>();
		mAttackTimer = Time::Time_s() + mAttackCD;
	}
}

void ZombieScript::CollisionStay(ICollider* other)
{
	if (other->GetGameObj()->mTag == "Plant")
	{
		if (Time::Time_s() >= mAttackTimer)
		{
			mAttackTimer += mAttackCD;
			mPlantLife->AddHP(-mDamage);
			// ֲ���������ָ�ǰ��
			//if (mPlantLife->GetCurrHP() <= 0.0f)
			//	ToWalking();
		}
	}
}

void ZombieScript::HPChange(float hp)
{
	SDL_Log("ZombieScript HP: %f", hp);
	// Ĭ�ϵ�Ѫ���䶯�ص���Ϊ0����
	if (hp <= 0.0f)
	{
		// ��Ҫֱ��ɾ��ֲ���ͨ����Ƥɾ��ֲ��
		// ��Ϊ��Ƥ���������ϵĶ��ֲ�
		// ���ֱ��ɾ��ֲ��ᵼ�²�Ƥ�޷���ֲ��ֲ��

		//Destroy(mGameObject);
		mWalkingSpeed = 0;
		//mPlantLife == nullptr;
		mCollider->SetEnable(false);	//������ײ����ֹ������������
		mAnim->Play("DeathBodyGIF");
		// �����ص������ض������������ٽ�ʬ����
		mAnim->AddActions("DeathBodyGIF", {
			{ 9, [this] {Destroy(mGameObject); }}
			});
	}
}
