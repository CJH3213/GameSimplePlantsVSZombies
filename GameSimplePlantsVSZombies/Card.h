#pragma once
#include "GameObject.h"
#include "Prefab.h"
#include <vector>

/// <summary>
/// ��ƬԤ�Ƽ�
/// ��֪����ôʵ��Ԥ�Ƽ����ȵ���һ����Ϸ����
/// ע�⣺��Ϸ�߼�ֻ��д�ڽű��ڣ�Ԥ�Ƽ�ֻ������ʵ����
/// </summary>
class Card :
	public Prefab
{
public:

	// ��дʵ��������
	virtual void Instantiate() override;
};

