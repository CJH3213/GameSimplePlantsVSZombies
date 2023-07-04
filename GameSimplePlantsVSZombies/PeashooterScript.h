#pragma once
#include "ComponentBase.h"
#include "BoxCollider.h"

class PeashooterScript :
    public ComponentBase
{
private:
	// �����㶹�����2�뷢��һ���㶹��
	float mInterval = 1.4f;
	// ��¼�´η���ʱ���
	float mNextTime = 0.0f;

	// ����������ɫ
	GameObject* mBackGround = nullptr;
	// ̽������ײ���
	BoxCollider* mDetectorCollider = nullptr;

	// ������ʬ̽����
	void CreateDetector();
	// ��ȡ̽�����ϵĽ�ʬ����
	size_t GetZombiesNum();

public:

	// ���
	virtual ComponentBase* Clone() const override;

	// �ű���ʼ��
	virtual void Awake() override;
	// �߼�����
	virtual void Update() override;

	// ����ֵ�仯�ص�
	void HPChange(float hp);
};

