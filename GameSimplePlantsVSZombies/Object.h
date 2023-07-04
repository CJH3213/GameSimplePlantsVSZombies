#pragma once
#include <string>
#include <typeinfo>

class Object
{
protected:

public:
	//获取当前类信息
	inline virtual const type_info& GetClassInfo() { return typeid(*this); }

};

