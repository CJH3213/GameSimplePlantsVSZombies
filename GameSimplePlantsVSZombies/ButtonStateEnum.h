#pragma once

//每个按键都有四个状态：无、按下、释放、保持
enum class ButtonState
{
    ENone,
    EPressed,
    EReleased,
    EHeld
};