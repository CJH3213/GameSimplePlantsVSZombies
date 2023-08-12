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
	mCollider->SetEnable(false);	//禁用碰撞器防止反复触发动画
	mAnim->Play("DeathBodyGIF");
	// 动画回调：倒地动画结束后销毁僵尸对象
	mAnim->AddActions("DeathBodyGIF", {
		{ 9, [this] {
			Destroy(mGameObject); }}
		});
}

void ZombieScript::Awake()
{
	// 获取场景音频脚本
	mAudio = GetScene()->FindGameObject("AdventureAudio")->GetComponent<AudioSource>();

	// 注册碰撞监听事件
	mCollider->mEnterEvents.AddListener("Enter", std::bind(&ZombieScript::CollisionEnter, this, _1));
	mCollider->mStayEvents.AddListener("Stay", std::bind(&ZombieScript::CollisionStay, this, _1));
	//mCollider->mExitEvents.AddListener("Exit", std::bind(&ZombieScript::CollisionExit, this, _1));

	// 监听生命值变化事件
	mZombieLife = mGameObject->GetComponent<LifeScript>();
	mZombieLife->mChangeEvents.AddListener("HPChange", [](float hp) {
		SDL_Log("ZombieScript HP: %f", hp);
		});

	// 校正y坐标
	GetTransform()->localPosition.y -= 25;

	mLastTime = Time::Time_s();
}

void ZombieScript::Update()
{
	if(mIsDead == false)
	{
		// 计算两帧间隔时间
		float deltaTime = Time::Time_s() - mLastTime;
		mLastTime = Time::Time_s();

		// 僵尸往左移动
		//mWalkingSpeed = 12;
		GetTransform()->localPosition.x -= deltaTime * mWalkingSpeed;

		// 如果走过了草坪，僵尸胜利
		if (GetTransform()->GetPosition().x < 3 && mIsFirstWinner == false)
		{
			mIsFirstWinner = true;
			// 把该事件通知到僵尸管理器
			mZomManager->ZombiesWon();
		}

		// 铲除植物后植物直接销毁，既不是扣血也不是碰撞分离
		// 在不想通过广播的方式情况下，目前只能通过判断碰撞物是否有植物
		// 如果没有和植物碰撞了，就恢复行走动作
		if (mPlantLife != nullptr && mCollider->IsEnable() == true &&
			IsCollisionWithPlant() == false)
			ToWalking();

		// 血量为0后转为死前处理
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
		&& mPlantLife == nullptr)	// 如果正在吃植物右侧又种下了，不要管右侧植物
	{
		mWalkingSpeed = 0;
		mAnim->Play("ChewingGIF");
		// 播放僵尸咀嚼音频
		mAudio->Play("Resource/Sounds/chomp.wav");

		mPlantLife = other->GetGameObj()->GetComponent<LifeScript>();
		mAttackTimer = Time::Time_s() + mAttackCD;
	}
	// 被割草机创到了，直接消失！
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

			// 播放僵尸咀嚼音频
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
		// 不能动
		mWalkingSpeed = 0;
		mAnim->SetFPS(0);
		// 不碰撞
		//mCollider->SetEnable(false);
	}
}
