#pragma once
#include "ComponentBase.h"
#include "BoxCollider.h"
#include "SpriteAnimator.h"
#include "LifeScript.h"
#include "AudioSource.h"

class ZombieScript :
	public ComponentBase
{
private:
	// 行走速度
	float mWalkingSpeed = 12.0f;
	// 上一帧时间
	float mLastTime = 0.0f;

	// 生命值
	//float mHealthValue = 100.0f;
	// 伤害值
	float mDamage = 10.0f;
	// 攻击间隔
	float mAttackCD = 0.8f;
	// 攻击专用计时器
	float mAttackTimer = 0.0f;

	// 当前僵尸已死亡吗
	bool mIsDead = false;
	// 当前僵尸是获胜者吗
	bool mIsFirstWinner = false;

	// 音频组件引用
	AudioSource* mAudio = nullptr;
	// 僵尸的生命组件
	LifeScript* mZombieLife = nullptr;
	// 植物的生命组件（引用缓存）
	LifeScript* mPlantLife = nullptr;

	// 当前是否与植物碰撞
	bool IsCollisionWithPlant();
	// 改变动作为行走
	void ToWalking();
	// 死亡
	void ToDeath();

public:
	// 碰撞组件
	BoxCollider* mCollider = nullptr;
	// 动画组件
	SpriteAnimator* mAnim = nullptr;
	// 僵尸管理器
	class ZombiesManager* mZomManager = nullptr;

	// 脚本初始
	virtual void Awake() override;
	// 逻辑更新
	virtual void Update() override;

	// 碰撞开始
	void CollisionEnter(ICollider* other);
	// 碰撞持续
	void CollisionStay(ICollider* other);
	// 碰撞分离
	//void CollisionExit(ICollider* other);
 
	// 停止运动
	void StopMove();
};

