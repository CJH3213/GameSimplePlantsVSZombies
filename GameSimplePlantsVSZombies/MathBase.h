#pragma once
#include <math.h>

namespace Math
{
	//近似最小值
	#define EPSILON 0.000001

	//定义π
	#ifndef M_PI
	#define M_PI 3.1415926535897
	#endif

	//算出弧度与角度的比率
	#define RAD_TO_DEG (180.0 / M_PI)

	//点，结构体
	typedef struct
	{
		int x;
		int y;
	} point_i;

	typedef struct
	{
		float x;
		float y;
	} point_f;

	//矩形，结构体
	typedef struct
	{
		int x, y;
		int w, h;
	} rectangle_i;

	//是否接近0
	extern bool NearZero(float f);
	//弧度转为角度
	extern double ToDegrees(double radian);

	//获取两者大值
	template<typename T>
	auto Max(const T &a, const T &b)
	{
		return b > a ? b : a;
	}

	//获取两者小值
	template<typename T>
	auto Min(const T& a, const T& b)
	{
		return b < a ? b : a;
	}

	//交换两者
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	////正弦函数
	//static float Sin(float r);
	////余弦函数
	//static float Cos(float r);
	////反余弦函数
	//static float Acos(float x);
	////正切函数
	//static float Tan(float r);
	////反正切函数1，[-pi/2,+pi/2]
	//static float Atan(float x);
	////反正切函数2，[-pi,+pi]
	//static float Atan2(float y, float x);
};

