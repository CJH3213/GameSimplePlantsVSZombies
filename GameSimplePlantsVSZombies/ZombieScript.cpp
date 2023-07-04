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
	// 注册碰撞监听事件
	mCollider->mEnterEvents.AddListener("Enter", std::bind(&ZombieScript::CollisionEnter, this, _1));
	mCollider->mStayEvents.AddListener("Stay", std::bind(&ZombieScript::CollisionStay, this, _1));
	//mCollider->mExitEvents.AddListener("Exit", std::bind(&ZombieScript::CollisionExit, this, _1));

	// 监听生命值变化事件
	mGameObject->GetComponent<LifeScript>()->mChangeEvents.
		AddListener("HPChange", std::bind(&ZombieScript::HPChange, this, _1));

	// 校正y坐标
	GetTransform()->localPosition.y -= 25;

	mLastTime = Time::Time_s();
}

void ZombieScript::Update()
{
	// 计算两帧间隔时间
	float deltaTime = Time::Time_s() - mLastTime;
	mLastTime = Time::Time_s();

	// 僵尸往左移动
	//mWalkingSpeed = 12;
	GetTransform()->localPosition.x -= deltaTime * mWalkingSpeed;
	if(GetTransform()->GetPosition().x < 0)
		GetTransform()->localPosition.x = 290;

	// 铲除植物后植物直接销毁，既不是扣血也不是碰撞分离
	// 在不想通过广播的方式情况下，目前只能通过判断碰撞物是否有植物
	// 如果没有和植物碰撞了，就恢复行走动作
	if (mPlantLife != nullptr && mCollider->IsEnable() == true &&
		IsCollisionWithPlant() == false)
		ToWalking();

}

void ZombieScript::CollisionEnter(ICollider* other)
{
	if (other->GetGameObj()->mTag == "Plant"
		&& mPlantLife == nullptr)	// 如果正在吃植物右侧又种下了，不要管右侧植物
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
			// 植物死亡，恢复前行
			//if (mPlantLife->GetCurrHP() <= 0.0f)
			//	ToWalking();
		}
	}
}

void ZombieScript::HPChange(float hp)
{
	SDL_Log("ZombieScript HP: %f", hp);
	// 默认的血量变动回调，为0死亡
	if (hp <= 0.0f)
	{
		// 不要直接删除植物，请通过草皮删除植物
		// 因为草皮管理着其上的多个植物，
		// 如果直接删除植物，会导致草皮无法种植新植物

		//Destroy(mGameObject);
		mWalkingSpeed = 0;
		//mPlantLife == nullptr;
		mCollider->SetEnable(false);	//禁用碰撞器防止反复触发动画
		mAnim->Play("DeathBodyGIF");
		// 动画回调：倒地动画结束后销毁僵尸对象
		mAnim->AddActions("DeathBodyGIF", {
			{ 9, [this] {Destroy(mGameObject); }}
			});
	}
}
