#pragma once
#include "MathBase.h"

/// <summary>
/// ��ά����
/// </summary>
class Vector2
{
public:
	float x = 0;
	float y = 0;

	// ��ͨ���캯��
	Vector2() noexcept : x(0), y(0) {};
	Vector2(float _x, float _y) noexcept : x(_x), y(_y) {};

	//��ȡ(0,0)����
	using Zero = Vector2;

	// �������캯��
	Vector2(const Vector2& v) noexcept : x(v.x), y(v.y) {};
	// ������ֵ�����
	Vector2& operator=(const Vector2& v) noexcept
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	// �ƶ����캯��
	Vector2(Vector2&& v) noexcept : x(v.x), y(v.y) {};
	// �ƶ���ֵ�����
	Vector2 operator=(Vector2&& v) noexcept
	{
		x = v.x;
		y = v.y;
		return *this;
	}


	//����ֵ
	inline void SetValue(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	//�ж����������Ƿ���ͬ
	inline bool operator==(const Vector2& v2) const
	{
		return (this->x == v2.x && this->y == v2.y);
	}

	//�������
	inline Vector2 operator-(const Vector2& v2) const
	{
		Vector2 v(*this);		//������ʱ����
		v.x -= v2.x;				//����
		v.y -= v2.y;
		return v;					//������ʱ����
	}

	//�����Լ�
	inline Vector2& operator-=(const Vector2& v2)
	{
		this->x -= v2.x;
		this->y -= v2.y;
		return *this;
	}

	//�������
	inline Vector2 operator+(const Vector2& v2) const
	{
		Vector2 v(*this);		//������ʱ����
		v.x += v2.x;				//����
		v.y += v2.y;
		return v;					//������ʱ����
	}

	//�����Լ�
	inline Vector2& operator+=(const Vector2& v2) 
	{
		this->x += v2.x;
		this->y += v2.y;
		return *this;
	};

	//���������˷�
	inline Vector2 operator*(const float f) const
	{
		Vector2 v(*this);		//������ʱ����
		v.x *= f;				//����
		v.y *= f;
		return v;					//������ʱ����
	}

	//�������˷�����Ԫ�س˷����ֳƹ��������
	// ����ʹ�õ���Ͳ������ʹ��dot��cross����
	inline Vector2 operator*(const Vector2& v2) const
	{
		Vector2 v(*this);		//������ʱ����
		v.x *= v2.x;				//����
		v.y *= v2.y;
		return v;					//������ʱ����
	}

	//���������Գ�
	inline Vector2& operator*=(const float f)
	{
		this->x *= f;
		this->y *= f;
		return *this;
	};

	//�����Գˣ���Ԫ�س˷����ֳƹ��������
	// ����ʹ�õ���Ͳ������ʹ��dot��cross����
	inline Vector2& operator*=(const Vector2& v2)
	{
		this->x *= v2.x;
		this->y *= v2.y;
		return *this;
	}

	//������������
	inline Vector2 operator/(const float f) const
	{
		Vector2 v(*this);		//������ʱ����
		v.x /= f;					//����
		v.y /= f;
		return v;					//������ʱ����
	}

	// �����Գ�
	inline Vector2& operator/=(const Vector2& v2)
	{
		this->x /= v2.x;
		this->y /= v2.y;
		return *this;
	}

	//����ģ����δ������ͨ�������Ƚϴ�С��������ʵ�ʳ��ȣ�
	inline float LengthUNSquared() const
	{
		return (this->x * this->x + this->y * this->y);
	};

	//����ģ����������ʵ�ʳ��ȣ��ȽϺ�ʱ��
	inline float LengthSquared() const 
	{
		return sqrtf(LengthUNSquared());
	};

	//����������׼������������תΪ��λ����1��
	bool NormalizeThis();
	//����һ����������׼������������������תΪ��λ����1��
	Vector2 NormalizeNew() const;

	// ����������������ʽ��ֵ��
	inline float Dot(const Vector2& v) const
	{
		return (this->x * v.x + this->y * v.y);
	};

	// ��ǰ��������ֵ��
	inline Vector2& AbsThis()
	{
		this->x = fabsf(this->x);
		this->y = fabsf(this->y);

		return *this;
	}
	// ȡ��������ֵ
	inline Vector2 AbsNew() const
	{
		Vector2 v;		//������ʱ����
		v.x = fabsf(this->x);
		v.y = fabsf(this->y);
		return v;					//������ʱ����
	}

	/// <summary>
	/// ����һԪһ�κ�����ͨ��x����y
	/// </summary>
	/// <param name="x">�����Ա���x</param>
	/// <param name="v1">�����ϵ�һ����</param>
	/// <param name="v2">�����ϵ���һ����</param>
	/// <returns>����������y</returns>
	static inline float LinearEquation(float x, const class Vector2& v1, const class Vector2& v2)
	{
		float k = (v1.y - v2.y) / (v1.x - v2.x);
		float b = v1.y - k * v1.x;

		return k * x + b;
	}

};

/*
��־��
22.02.22��������������ⲿ��Ҫ���ã�����Ӧ�ú�����д��һ�𣬼���������ֱ��д�������ϣ�����д��cpp�ļ������ֻ�����Լ��õ������������Էֿ�д��

*/

