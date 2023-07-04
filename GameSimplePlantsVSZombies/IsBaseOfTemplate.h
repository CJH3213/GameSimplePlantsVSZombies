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
��־��
22.02.24��֧�ִ�ģ������������жϼ̳У�������Դ��https://yebd1h.smartapps.cn/pages/blog/index?blogId=108382265&_swebfr=1&_swebFromHost=baiduboxapp
				 ������⣺�ȼ������C��ģ���࣬std::declval<T*>()��ȡ��T*ָ����������ͣ�����is_base_of_template_impl()����������T*��
								���T*���Դ�������͵Ļ���ָ��������������ͱ�������Ts...���յ��������ԣ���˵��T��C�����࣬������������Ϊstd::true_type��
								is_base_of_template_impl(...)�������շ�C<>*���͵Ĳ�������������Ϊstd::false_type��
								decltype()���Ժ�����ֵ��ȡ�������ķ�������std::true_type��std::false_type������::valueȡ��boolֵ��
*/
