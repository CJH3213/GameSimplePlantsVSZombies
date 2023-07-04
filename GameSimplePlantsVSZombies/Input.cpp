#include "Input.h"
#include <SDL.h>

Vector2 Input::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return Vector2(x, y);
}

bool Input::GetMouseButton(int buttonID)
{
	switch (buttonID)
	{
	case 0:		// ���
		return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT);
	case 1:		// �Ҽ�
		return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT);
	case 2:		// �м�
		return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
	default:
		return false;
	}
}
