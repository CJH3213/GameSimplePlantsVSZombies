#pragma once
#include "Prefab.h"

class Zombie :
    public Prefab
{
public:
    // Ԥ�Ƽ�ʵ����д������
    virtual void Instantiate() override;
};

