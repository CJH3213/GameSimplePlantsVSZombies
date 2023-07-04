#include "MouseState.h"

void MouseState::PrepareForUpdate()
{
	mPrevButtons = mCurrButtons;
}

void MouseState::Update()
{
	int x = 0, y = 0;
	//��ȡ����ָ������Ͱ���״̬
	mCurrButtons = SDL_GetMouseState(&x, &y);
	mMousePos.x = static_cast<float>(x);
	mMousePos.y = static_cast<float>(y);
}

/// <summary>
/// ��ȡ��갴��״̬
/// </summary>
/// <param name="button">1Ϊ�����2Ϊ�м���3Ϊ�Ҽ�</param>
/// <returns>ButtonStateö�����͵İ���״̬</returns>
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