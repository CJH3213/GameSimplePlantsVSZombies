#pragma once
#include "MathBase.h"

/// <summary>
/// 二维向量
/// </summary>
class Vector2
{
public:
	float x = 0;
	float y = 0;

	// 普通构造函数
	Vector2() noexcept : x(0), y(0) {};
	Vector2(float _x, float _y) noexcept : x(_x), y(_y) {};

	//获取(0,0)向量
	using Zero = Vector2;

	// 拷贝构造函数
	Vector2(const Vector2& v) noexcept : x(v.x), y(v.y) {};
	// 拷贝赋值运算符
	Vector2& operator=(const Vector2& v) noexcept
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	// 移动构造函数
	Vector2(Vector2&& v) noexcept : x(v.x), y(v.y) {};
	// 移动赋值运算符
	Vector2 operator=(Vector2&& v) noexcept
	{
		x = v.x;
		y = v.y;
		return *this;
	}


	//设置值
	inline void SetValue(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	//判断两个向量是否相同
	inline bool operator==(const Vector2& v2) const
	{
		return (this->x == v2.x && this->y == v2.y);
	}

	//向量相减
	inline Vector2 operator-(const Vector2& v2) const
	{
		Vector2 v(*this);		//创建临时对象
		v.x -= v2.x;				//运算
		v.y -= v2.y;
		return v;					//返回临时对象
	}

	//向量自减
	inline Vector2& operator-=(const Vector2& v2)
	{
		this->x -= v2.x;
		this->y -= v2.y;
		return *this;
	}

	//向量相加
	inline Vector2 operator+(const Vector2& v2) const
	{
		Vector2 v(*this);		//创建临时对象
		v.x += v2.x;				//运算
		v.y += v2.y;
		return v;					//返回临时对象
	}

	//向量自加
	inline Vector2& operator+=(const Vector2& v2) 
	{
		this->x += v2.x;
		this->y += v2.y;
		return *this;
	};

	//向量标量乘法
	inline Vector2 operator*(const float f) const
	{
		Vector2 v(*this);		//创建临时对象
		v.x *= f;				//运算
		v.y *= f;
		return v;					//返回临时对象
	}

	//两向量乘法（逐元素乘法，又称哈达玛积）
	// 如需使用点积和叉积，请使用dot和cross方法
	inline Vector2 operator*(const Vector2& v2) const
	{
		Vector2 v(*this);		//创建临时对象
		v.x *= v2.x;				//运算
		v.y *= v2.y;
		return v;					//返回临时对象
	}

	//向量标量自乘
	inline Vector2& operator*=(const float f)
	{
		this->x *= f;
		this->y *= f;
		return *this;
	};

	//向量自乘（逐元素乘法，又称哈达玛积）
	// 如需使用点积和叉积，请使用dot和cross方法
	inline Vector2& operator*=(const Vector2& v2)
	{
		this->x *= v2.x;
		this->y *= v2.y;
		return *this;
	}

	//向量标量除法
	inline Vector2 operator/(const float f) const
	{
		Vector2 v(*this);		//创建临时对象
		v.x /= f;					//运算
		v.y /= f;
		return v;					//返回临时对象
	}

	// 向量自除
	inline Vector2& operator/=(const Vector2& v2)
	{
		this->x /= v2.x;
		this->y /= v2.y;
		return *this;
	}

	//向量模长（未开方，通常用来比较大小而不在意实际长度）
	inline float LengthUNSquared() const
	{
		return (this->x * this->x + this->y * this->y);
	};

	//向量模长（开方，实际长度，比较耗时）
	inline float LengthSquared() const 
	{
		return sqrtf(LengthUNSquared());
	};

	//将本向量标准化（向量长度转为单位长度1）
	bool NormalizeThis();
	//返回一个本向量标准化的向量（向量长度转为单位长度1）
	Vector2 NormalizeNew() const;

	// 向量点积（点积代数式求值）
	inline float Dot(const Vector2& v) const
	{
		return (this->x * v.x + this->y * v.y);
	};

	// 当前向量绝对值化
	inline Vector2& AbsThis()
	{
		this->x = fabsf(this->x);
		this->y = fabsf(this->y);

		return *this;
	}
	// 取向量绝对值
	inline Vector2 AbsNew() const
	{
		Vector2 v;		//创建临时对象
		v.x = fabsf(this->x);
		v.y = fabsf(this->y);
		return v;					//返回临时对象
	}

	/// <summary>
	/// 解析一元一次函数并通过x计算y
	/// </summary>
	/// <param name="x">传入自变量x</param>
	/// <param name="v1">函数上的一个点</param>
	/// <param name="v2">函数上的另一个点</param>
	/// <returns>算出的因变量y</returns>
	static inline float LinearEquation(float x, const class Vector2& v1, const class Vector2& v2)
	{
		float k = (v1.y - v2.y) / (v1.x - v2.x);
		float b = v1.y - k * v1.x;

		return k * x + b;
	}

};

/*
日志：
22.02.22：内联函数如果外部需要调用，定义应该和声明写在一起，即函数定义直接写在声明上，不能写到cpp文件；如果只是类自己用的内联函数可以分开写。

*/

