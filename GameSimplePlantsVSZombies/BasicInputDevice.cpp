#include "BasicInputDevice.h"

/// <summary>
/// 通过虚函数，返回子类的type_info
/// </summary>
/// <returns></returns>
const type_info& BasicInputDevice::GetClassInfo()
{
	return typeid(*this);
}
