#pragma once
#include "Vector2.h"

class Input
{
public:

	// 获取鼠标坐标
	static Vector2 GetMousePosition();
	// 判断鼠标按键
	static bool GetMouseButton(int buttonID);
};

