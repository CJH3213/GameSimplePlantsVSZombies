#include "BasicInputDevice.h"

/// <summary>
/// ͨ���麯�������������type_info
/// </summary>
/// <returns></returns>
const type_info& BasicInputDevice::GetClassInfo()
{
	return typeid(*this);
}
