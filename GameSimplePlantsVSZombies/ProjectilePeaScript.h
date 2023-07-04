#pragma once
#include "ComponentBase.h"
#include "BoxCollider.h"

class ProjectilePeaScript :
	public ComponentBase
{
private:
	// �ӵ��ƶ��ٶȣ�����ÿ�룩
	float mSpeed = 100.0f;
	// ��һ֡ʱ�䣨��������֡�����
	float mLastTime = 0.0f;

	// �ӵ��˺�ֵ
	float mDamage = 20.0f;

	// �ӵ�������ײ������
	BoxCollider* mCollider = nullptr;

public:

	// ���
	virtual ComponentBase* Clone() const override;

	// �ű���ʼ��
	virtual void Awake() override;
	// �߼�����
	virtual void Update() override;

	// ��ײ��ʼ�ص�
	void CollisionEnter(ICollider* other);
};

