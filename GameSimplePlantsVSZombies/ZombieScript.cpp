#include "ZombieScript.h"
#include "TransformComponent.h"
#include "Time.h"
#include "SceneBase.h"
#include "TurfScript.h"
#include "Random.h"
#include "ZombiesManager.h"
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

void ZombieScript::ToDeath()
{
	mWalkingSpeed = 0;
	//mPlantLife == nullptr;
	mCollider->SetEnable(false);	//������ײ����ֹ������������
	mAnim->Play("DeathBodyGIF");
	// �����ص������ض������������ٽ�ʬ����
	mAnim->AddActions("DeathBodyGIF", {
		{ 9, [this] {
			Destroy(mGameObject); }}
		});
}

void ZombieScript::Awake()
{
	// ��ȡ������Ƶ�ű�
	mAudio = GetScene()->FindGameObject("AdventureAudio")->GetComponent<AudioSource>();

	// ע����ײ�����¼�
	mCollider->mEnterEvents.AddListener("Enter", std::bind(&ZombieScript::CollisionEnter, this, _1));
	mCollider->mStayEvents.AddListener("Stay", std::bind(&ZombieScript::CollisionStay, this, _1));
	//mCollider->mExitEvents.AddListener("Exit", std::bind(&ZombieScript::CollisionExit, this, _1));

	// ��������ֵ�仯�¼�
	mZombieLife = mGameObject->GetComponent<LifeScript>();
	mZombieLife->mChangeEvents.AddListener("HPChange", [](float hp) {
		SDL_Log("ZombieScript HP: %f", hp);
		});

	// У��y����
	GetTransform()->localPosition.y -= 25;

	mLastTime = Time::Time_s();
}

void ZombieScript::Update()
{
	if(mIsDead == false)
	{
		// ������֡���ʱ��
		float deltaTime = Time::Time_s() - mLastTime;
		mLastTime = Time::Time_s();

		// ��ʬ�����ƶ�
		//mWalkingSpeed = 12;
		GetTransform()->localPosition.x -= deltaTime * mWalkingSpeed;

		// ����߹��˲�ƺ����ʬʤ��
		if (GetTransform()->GetPosition().x < 3 && mIsFirstWinner == false)
		{
			mIsFirstWinner = true;
			// �Ѹ��¼�֪ͨ����ʬ������
			mZomManager->ZombiesWon();
		}

		// ����ֲ���ֲ��ֱ�����٣��Ȳ��ǿ�ѪҲ������ײ����
		// �ڲ���ͨ���㲥�ķ�ʽ����£�Ŀǰֻ��ͨ���ж���ײ���Ƿ���ֲ��
		// ���û�к�ֲ����ײ�ˣ��ͻָ����߶���
		if (mPlantLife != nullptr && mCollider->IsEnable() == true &&
			IsCollisionWithPlant() == false)
			ToWalking();

		// Ѫ��Ϊ0��תΪ��ǰ����
		if (mZombieLife->GetCurrHP() <= 0.0f)
		{
			mIsDead = true;
			ToDeath();
		}
	}
}

void ZombieScript::CollisionEnter(ICollider* other)
{
	if (other->GetGameObj()->mTag == "Plant"
		&& mPlantLife == nullptr)	// ������ڳ�ֲ���Ҳ��������ˣ���Ҫ���Ҳ�ֲ��
	{
		mWalkingSpeed = 0;
		mAnim->Play("ChewingGIF");
		// ���Ž�ʬ�׽���Ƶ
		mAudio->Play("Resource/Sounds/chomp.wav");

		mPlantLife = other->GetGameObj()->GetComponent<LifeScript>();
		mAttackTimer = Time::Time_s() + mAttackCD;
	}
	// ����ݻ������ˣ�ֱ����ʧ��
	else if (other->GetGameObj()->mTag == "LawnMower")
	{
		mZombieLife->SetHp(0.0f);
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

			// ���Ž�ʬ�׽���Ƶ
			int r = Random(0, 10);
			if(r % 2)
				mAudio->Play("Resource/Sounds/chomp.wav");
			else
				mAudio->Play("Resource/Sounds/chomp2.wav");
		}
	}
}

void ZombieScript::StopMove()
{
	if(mIsFirstWinner == false)
	{
		// ���ܶ�
		mWalkingSpeed = 0;
		mAnim->SetFPS(0);
		// ����ײ
		//mCollider->SetEnable(false);
	}
}
