#pragma once
#include "ComponentBase.h"
#include <array>
#include "Vector2.h"

class ZombiesManager :
	public ComponentBase
{
private:
	// ���ɽ�ʬ�ļ��
	float mInterval = 10.0f;
	// �´����ɽ�ʬ��ʱ��
	float mNextTime = 0.0f;

	// ÿ������λ��x
	std::array<float, 5> mBeginPos = {125, 225, 325, 425, 525};

	// ����ͼƬ��������
	GameObject* mBackGround = nullptr;

public:
	// ��ս��ʼ���������
	virtual void OnEnable() override;

	// �ű���ʼ��
	virtual void Start() override;
	// �߼�����
	virtual void Update() override;
};

