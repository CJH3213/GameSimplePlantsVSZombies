#pragma once
#include "SceneBase.h"

class LoadingPageScene :
    public SceneBase
{
private:

public:
    LoadingPageScene(std::string name);

    // 场景加载和实例化对象
    virtual void Start() override;

};

/*
    加载页面及欢迎界面，主体为一张背景图和下方的加载进度条。
    进度条以草卷铺开的形式，由一张矩形草皮纹理和一张圆形草卷构成，
    草卷始终保持在草皮的最右端，草卷左侧固定，显示长度为进度比例，同时草卷旋转角度也和进度有关。
*/

