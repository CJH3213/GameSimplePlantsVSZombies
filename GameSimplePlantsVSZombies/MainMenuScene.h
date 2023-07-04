#pragma once
#include "SceneBase.h"

class MainMenuScene :
    public SceneBase
{
private:

public:
    MainMenuScene(std::string name);

    // 场景加载和实例化对象
    virtual void Start() override;
};

/*
日志：
22.02.24：添加物体（或组件）在构造函数处添加；往上级（持有者）获取资源在Start()函数处执行；
                 因为构造函数处用来实例化对象，全部对象实例完毕后才会调用Start()函数，此时就不会获取到空指针。
*/
