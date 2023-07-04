#pragma once
#include "Prefab.h"

class Zombie :
    public Prefab
{
public:
    // 预制件实例化写到这里
    virtual void Instantiate() override;
};

