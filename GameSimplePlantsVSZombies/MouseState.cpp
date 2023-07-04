#include "MouseState.h"

void MouseState::PrepareForUpdate()
{
	mPrevButtons = mCurrButtons;
}

void MouseState::Update()
{
	int x = 0, y = 0;
	//获取鼠标的指针坐标和按键状态
	mCurrButtons = SDL_GetMouseState(&x, &y);
	mMousePos.x = static_cast<float>(x);
	mMousePos.y = static_cast<float>(y);
}

/// <summary>
/// 获取鼠标按键状态
/// </summary>
/// <param name="button">1为左键、2为中键、3为右键</param>
/// <returns>ButtonState枚举类型的按键状态</returns>
ButtonState MouseState::GetButtonState(int button) const
{
	if ((mPrevButtons & button) == 0)
	{
		if ((mCurrButtons & button) == 0)
			return ButtonState::ENone;
		else
			return ButtonState::EPressed;
	}
	else
	{
		if ((mCurrButtons & button) == 0)
			return  ButtonState::EReleased;
		else
			return  ButtonState::EHeld;
	}
}