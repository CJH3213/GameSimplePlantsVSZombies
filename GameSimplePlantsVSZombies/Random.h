#pragma once
#include <random>
#include <type_traits>

/// <summary>
/// ������������������ࣩ
/// ��װC++11��random���һ�ֲ������������
/// random_device + mt19937 + uniform_int_distribution
/// </summary>
template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
inline T Random(T min, T max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	if constexpr (std::is_integral_v<T>)
	{
		std::uniform_int_distribution<T> dis(min, max);
		return dis(gen);
	}
	else
	{
		std::uniform_real_distribution<T> dis(min, max);
		return dis(gen);
	}
}

/*
��SFINAE����Substitution Failure Is Not An Error������
std::enable_if_t�������ڼ��T���;����Ƿ��������ɶ�Ӧ����ģ��
std::is_arithmetic_v<T>�����T�����Ƿ�Ϊ��������
, int> = 0��=0��˵��ģ�����λ�ÿ��Բ����룬Ĭ��ֵΪint����0ֵ

if constexpr (std::is_integral_v<T>)
C++17����if����ڱ����ڼ����ִ�����ݣ�������ʱ
std::is_integral_v<T>���ж�T�����Ƿ�Ϊ����
*/