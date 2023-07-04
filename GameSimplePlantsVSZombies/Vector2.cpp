#include "Vector2.h"


inline bool Vector2::NormalizeThis()
{
	//�������ǰ����ģ��
	float lengthS = LengthSquared();

	//��������ӽ�0����Ҫִ�г���
	if (Math::NearZero(lengthS))
		return false;

	lengthS = 1 / lengthS;		//ȷ����ĸ��ģ��������0�����Լ��㵹��
	(*this) *= lengthS;			//��ǰ�����Գ�ģ���ĵ��������ڳ�������	

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
