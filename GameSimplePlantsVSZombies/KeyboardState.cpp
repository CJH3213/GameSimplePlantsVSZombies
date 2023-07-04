#include "KeyboardState.h"
#include <string.h>

void KeyboardState::Initialize()
{
	mCurrState = SDL_GetKeyboardState(NULL);

	//��������
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
	//����ǰ�����ΰ���״̬�жϰ�������
	if (mPrevState[keyCode] == 0)
	{
		if (mCurrState[keyCode] == 0)
			return ButtonState::ENone;	//�����ͷ�
		else
			return ButtonState::EPressed;	//�հ���
	}
	else
	{
		if (mCurrState[keyCode] == 0)
			return ButtonState::EReleased;		//���ͷ�
		else
			return ButtonState::EHeld;		//���ְ���
	}
}