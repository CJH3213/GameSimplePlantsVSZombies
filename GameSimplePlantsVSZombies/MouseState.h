#pragma once
#include "BasicInputDevice.h"
#include "ButtonStateEnum.h"
#include "Vector2.h"
#include <SDL.h>

class MouseState :
    public BasicInputDevice
{
private:
    //指针坐标
    Vector2 mMousePos;
    //按键状态
    Uint32 mCurrButtons;
    Uint32 mPrevButtons;
public:
    //更新前准备
    void PrepareForUpdate() override;
    //更新
    void Update() override;

    //用户获取鼠标指针位置
    const Vector2& GetPosition() const { return mMousePos; }
    //用户获取鼠标按键状态
    ButtonState GetButtonState(int button) const;

};

