#pragma once
#include "Vector2.h"

class Input
{
public:

	// ��ȡ�������
	static Vector2 GetMousePosition();
	// �ж���갴��
	static bool GetMouseButton(int buttonID);
};

