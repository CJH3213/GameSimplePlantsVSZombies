#pragma once
#include <math.h>

namespace Math
{
	//������Сֵ
	#define EPSILON 0.000001

	//�����
	#ifndef M_PI
	#define M_PI 3.1415926535897
	#endif

	//���������Ƕȵı���
	#define RAD_TO_DEG (180.0 / M_PI)

	//�㣬�ṹ��
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

	//���Σ��ṹ��
	typedef struct
	{
		int x, y;
		int w, h;
	} rectangle_i;

	//�Ƿ�ӽ�0
	extern bool NearZero(float f);
	//����תΪ�Ƕ�
	extern double ToDegrees(double radian);

	//��ȡ���ߴ�ֵ
	template<typename T>
	auto Max(const T &a, const T &b)
	{
		return b > a ? b : a;
	}

	//��ȡ����Сֵ
	template<typename T>
	auto Min(const T& a, const T& b)
	{
		return b < a ? b : a;
	}

	//��������
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	////���Һ���
	//static float Sin(float r);
	////���Һ���
	//static float Cos(float r);
	////�����Һ���
	//static float Acos(float x);
	////���к���
	//static float Tan(float r);
	////�����к���1��[-pi/2,+pi/2]
	//static float Atan(float x);
	////�����к���2��[-pi,+pi]
	//static float Atan2(float y, float x);
};

