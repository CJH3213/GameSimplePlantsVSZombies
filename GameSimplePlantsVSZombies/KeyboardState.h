#pragma once
#include "BasicInputDevice.h"
#include "ButtonStateEnum.h"
#include <SDL.h>

class KeyboardState :
    public BasicInputDevice
{
private:
    //当前状态
    const Uint8* mCurrState;
    //状态暂存器
    Uint8 mPrevState[SDL_NUM_SCANCODES];

public:

    //初始化
    void Initialize() override;
    //更新前准备
    void PrepareForUpdate() override;
    //更新：由于获取到SDL键盘状态的指针，因此只需要更新消息泵即可更新按键新状态

    //获取当前按键电平
    bool GetKeyValue(SDL_Scancode keyCode) const;
    //获取按键动作状态
    enum ButtonState GetKeyState(SDL_Scancode keyCode) const;
};

