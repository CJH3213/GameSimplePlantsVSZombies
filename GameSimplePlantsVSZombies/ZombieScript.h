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
	// �����ٶ�
	float mWalkingSpeed = 12.0f;
	// ��һ֡ʱ��
	float mLastTime = 0.0f;

	// ����ֵ
	//float mHealthValue = 100.0f;
	// �˺�ֵ
	float mDamage = 10.0f;
	// �������
	float mAttackCD = 0.8f;
	// ����ר�ü�ʱ��
	float mAttackTimer = 0.0f;

	// ��ǰ��ʬ��������
	bool mIsDead = false;
	// ��ǰ��ʬ�ǻ�ʤ����
	bool mIsFirstWinner = false;

	// ��Ƶ�������
	AudioSource* mAudio = nullptr;
	// ��ʬ���������
	LifeScript* mZombieLife = nullptr;
	// ֲ���������������û��棩
	LifeScript* mPlantLife = nullptr;

	// ��ǰ�Ƿ���ֲ����ײ
	bool IsCollisionWithPlant();
	// �ı䶯��Ϊ����
	void ToWalking();
	// ����
	void ToDeath();

public:
	// ��ײ���
	BoxCollider* mCollider = nullptr;
	// �������
	SpriteAnimator* mAnim = nullptr;
	// ��ʬ������
	class ZombiesManager* mZomManager = nullptr;

	// �ű���ʼ
	virtual void Awake() override;
	// �߼�����
	virtual void Update() override;

	// ��ײ��ʼ
	void CollisionEnter(ICollider* other);
	// ��ײ����
	void CollisionStay(ICollider* other);
	// ��ײ����
	//void CollisionExit(ICollider* other);
 
	// ֹͣ�˶�
	void StopMove();
};

