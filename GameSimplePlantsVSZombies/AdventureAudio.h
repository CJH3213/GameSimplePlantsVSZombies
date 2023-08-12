#pragma once
#include "Prefab.h"

class AdventureAudio :
    public Prefab
{
public:
    // 重写实例化方法
    virtual void Instantiate() override;
};

