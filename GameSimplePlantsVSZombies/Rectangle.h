#pragma once
#include "Vector2.h"

class Rectangle
{
public:
	Vector2 mCenter;	// ������������
	Vector2 mSize;		// ���δ�С

	// ���캯��
	Rectangle(const Vector2& center, const Vector2& size);
	Rectangle();

	// ��ȡ�����Ķ���
	Vector2 GetTopLeftPoint() const;
	Vector2 GetTopRightPoint() const;
	Vector2 GetBottomLeftPoint() const;
	Vector2 GetBottomRightPoint() const;
	// ��ȡ�����������е�
	Vector2 GetCenterPoint() const;
	Vector2 GetLeftCenterPoint() const;
	Vector2 GetRightCenterPoint() const;
	Vector2 GetTopCenterPoint() const;
	Vector2 GetBottomCenterPoint() const;

	// �������Ƿ��ཻ
	bool IsIntersect(const Rectangle& rect) const;
	// ��ǰ���α���������һ������
	bool IsInside(Rectangle& rect) const;
	// �Ƿ���ͬ
	bool IsSame(Rectangle& rect) const;

	// �����Ƿ�����ཻ
	bool IsIntersect(const Vector2& pos) const;
};


/*
//���Ծ�����
Rectangle rect1;
rect1.mCenter = Vector2(2, 0);
rect1.mSize = Vector2(20, 20);

Rectangle rect2;
rect2.mCenter = Vector2(0, 0);
rect2.mSize = Vector2(20, 20);

bool b1 = rect1.IsInside(rect2);
bool b2 = rect1.IsIntersect(rect2);
bool b3 = rect1.IsSame(rect2);
*/

