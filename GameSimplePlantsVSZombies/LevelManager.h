#pragma once
#include "Prefab.h"

class LevelManager :
    public Prefab
{
public:
    // Ԥ�Ƽ�ʵ����д������
    virtual void Instantiate() override;
};

