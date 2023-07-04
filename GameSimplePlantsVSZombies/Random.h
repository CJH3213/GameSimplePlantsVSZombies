#pragma once
#include <random>
#include <type_traits>

/// <summary>
/// 随机数生成器（单例类）
/// 封装C++11的random库的一种产生随机数方法
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
“SFINAE”（Substitution Failure Is Not An Error）技术
std::enable_if_t：编译期检查T类型决定是否启用生成对应类型模板
std::is_arithmetic_v<T>：检查T类型是否为算术类型
, int> = 0：=0是说该模板参数位置可以不输入，默认值为int类型0值

if constexpr (std::is_integral_v<T>)
C++17，该if语句在编译期间决定执行内容，非运行时
std::is_integral_v<T>：判断T类型是否为整型
*/