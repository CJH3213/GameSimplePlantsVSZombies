#pragma once
#include <SDL.h>

struct Color
{
	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	inline SDL_Color GetSDLColor()
	{
		return { r, g, b, a };
	}

	// �����ǳ�����ɫ
	static const Color Red;
	static const Color Green;
	static const Color Blue;
};

