#pragma once
#include "GameObject.h"

class Prefab :
	public GameObject
{
private:

public:
	// ���캯��
	Prefab();
	// ��������
	//~Prefab();

	// Ԥ�Ƽ�ʵ����д������
	virtual void Instantiate() {};
};

