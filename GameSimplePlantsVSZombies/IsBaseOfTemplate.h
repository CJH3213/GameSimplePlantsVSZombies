#pragma once
#include <type_traits>


// case1: T* can cast to C*
template <template <typename...> class C, typename...Ts>
std::true_type is_base_of_template_impl(const C<Ts...>*);

// case2: T* cannot cast to C*
template <template <typename...> class C>
std::false_type is_base_of_template_impl(...);

template <template <typename...> class C, typename T>
using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()));

/*
日志：
22.02.24：支持带模板子类与基类判断继承，程序来源：https://yebd1h.smartapps.cn/pages/blog/index?blogId=108382265&_swebfr=1&_swebFromHost=baiduboxapp
				 功能理解：先假设基类C是模板类，std::declval<T*>()获取到T*指针的引用类型，调用is_base_of_template_impl()函数并传入T*，
								如果T*可以传入带泛型的基类指针参数，泛型类型被参数包Ts...吸收掉（即忽略），说明T是C的子类，函数返回类型为std::true_type；
								is_base_of_template_impl(...)负责吸收非C<>*类型的参数，返回类型为std::false_type；
								decltype()忽略函数的值，取出函数的返回类型std::true_type或std::false_type，再用::value取出bool值。
*/
