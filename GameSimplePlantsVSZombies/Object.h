#pragma once
#include <string>
#include <typeinfo>

class Object
{
protected:

public:
	//��ȡ��ǰ����Ϣ
	inline virtual const type_info& GetClassInfo() { return typeid(*this); }

};

