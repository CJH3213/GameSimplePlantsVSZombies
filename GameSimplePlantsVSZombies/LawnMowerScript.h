#pragma once
#include "ComponentBase.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "AudioSource.h"

class LawnMowerScript :
	public ComponentBase
{
private:
	// 速度
	//float mSpeed = 10.0f;
	// 由于小车是一次性的，标记是否已经使用
	bool mIsUsed = false;

	// 音频组件引用
	AudioSource* mAudio = nullptr;

public:
	// 动作组件
	Animator* mAnim = nullptr;
	// 碰撞组件
	BoxCollider* mCollider = nullptr;

	// 脚本初始化
	virtual void Awake() override;
	// 逻辑更新
	virtual void Update() override;

	// 碰撞开始
	void CollisionEnter(ICollider* other);
};

