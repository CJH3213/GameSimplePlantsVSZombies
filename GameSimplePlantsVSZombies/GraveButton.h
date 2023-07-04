#pragma once
#include "ImageButton.h"

class GraveButton :
    public ImageButton
{
private:

public:
    // 构造函数
    GraveButton(
        std::string normalPath,
        std::string highLigPath);

    // 组件初始化
    virtual void Awake();

    // 鼠标点击碰撞器的第一帧（点击）
    void OnMouseDown();
    // 鼠标点击碰撞器的第一帧（点击）
    void OnMouseUp();
};

