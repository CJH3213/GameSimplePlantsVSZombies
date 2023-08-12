#pragma once
#include "ComponentBase.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "AudioSource.h"

class LawnMowerScript :
	public ComponentBase
{
private:
	// �ٶ�
	//float mSpeed = 10.0f;
	// ����С����һ���Եģ�����Ƿ��Ѿ�ʹ��
	bool mIsUsed = false;

	// ��Ƶ�������
	AudioSource* mAudio = nullptr;

public:
	// �������
	Animator* mAnim = nullptr;
	// ��ײ���
	BoxCollider* mCollider = nullptr;

	// �ű���ʼ��
	virtual void Awake() override;
	// �߼�����
	virtual void Update() override;

	// ��ײ��ʼ
	void CollisionEnter(ICollider* other);
};

