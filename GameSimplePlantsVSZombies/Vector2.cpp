#include "Vector2.h"


inline bool Vector2::NormalizeThis()
{
	//先算出当前向量模长
	float lengthS = LengthSquared();

	//如果除数接近0，不要执行除法
	if (Math::NearZero(lengthS))
		return false;

	lengthS = 1 / lengthS;		//确定分母（模长）不是0，可以计算倒数
	(*this) *= lengthS;			//当前向量自乘模长的倒数，等于除法运算	

	return true;
}

inline Vector2 Vector2::NormalizeNew() const
{
	Vector2 v(*this);
	v.NormalizeThis();

	return v;
}

//inline float Vector2::Dot(const Vector2& v)
//{
//	return (this->x * v.x + this->y * v.y);
//}
