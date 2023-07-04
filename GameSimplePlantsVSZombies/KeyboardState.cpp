#include "KeyboardState.h"
#include <string.h>

void KeyboardState::Initialize()
{
	mCurrState = SDL_GetKeyboardState(NULL);

	//清零数组
	memset(mPrevState, 0, SDL_NUM_SCANCODES);
}

void KeyboardState::PrepareForUpdate()
{
	memcpy(mPrevState, mCurrState, SDL_NUM_SCANCODES);
}

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	if (mCurrState[keyCode] == 0)
		return false;
	else
		return true;
}

enum ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	//根据前后两次按键状态判断按键动作
	if (mPrevState[keyCode] == 0)
	{
		if (mCurrState[keyCode] == 0)
			return ButtonState::ENone;	//保持释放
		else
			return ButtonState::EPressed;	//刚按下
	}
	else
	{
		if (mCurrState[keyCode] == 0)
			return ButtonState::EReleased;		//刚释放
		else
			return ButtonState::EHeld;		//保持按下
	}
}