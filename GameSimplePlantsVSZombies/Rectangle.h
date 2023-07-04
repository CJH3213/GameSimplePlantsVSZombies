#pragma once
#include "Vector2.h"

class Rectangle
{
public:
	Vector2 mCenter;	// 矩形中心坐标
	Vector2 mSize;		// 矩形大小

	// 构造函数
	Rectangle(const Vector2& center, const Vector2& size);
	Rectangle();

	// 获取矩形四顶点
	Vector2 GetTopLeftPoint() const;
	Vector2 GetTopRightPoint() const;
	Vector2 GetBottomLeftPoint() const;
	Vector2 GetBottomRightPoint() const;
	// 获取矩形四条边中点
	Vector2 GetCenterPoint() const;
	Vector2 GetLeftCenterPoint() const;
	Vector2 GetRightCenterPoint() const;
	Vector2 GetTopCenterPoint() const;
	Vector2 GetBottomCenterPoint() const;

	// 两矩形是否相交
	bool IsIntersect(const Rectangle& rect) const;
	// 当前矩形被包含于另一矩形内
	bool IsInside(Rectangle& rect) const;
	// 是否相同
	bool IsSame(Rectangle& rect) const;

	// 矩形是否与点相交
	bool IsIntersect(const Vector2& pos) const;
};


/*
//测试矩形类
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

