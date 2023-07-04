#pragma once
#include "ComponentBase.h"
#include "Vector2.h"

/// <summary>
/// �ڲ�Ƥ�������������
/// </summary>
class SunCreatorScript :
	public ComponentBase
{
private:
	// �´����������ʱ���
	float mNextTime = 0.0f;

public:
	// ���ϲ�Ƥ����
	Vector2 mGrassTLPos;
	// ���½ǲ�Ƥ����
	Vector2 mGrassBRPos;

	// �ű���ʼ��
	virtual void Awake() override;

	// �߼�����
	virtual void Update() override;
};

