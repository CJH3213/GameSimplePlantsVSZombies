#pragma once
#include "GameObject.h"
#include <vector>
#include "Prefab.h"

class CardBank :
	public Prefab
{
public:
	// ��дʵ��������
	virtual void Instantiate() override;
};
