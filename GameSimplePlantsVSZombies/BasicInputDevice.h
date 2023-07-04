#pragma once
#include <typeinfo>

class BasicInputDevice
{
private:

public:
	//初始化和关闭
	virtual void Initialize() {}
	virtual void Shutdown() {}

	//更新前的准备
	virtual void PrepareForUpdate() {}
	//更新
	virtual void Update(){}

	//获取当前类信息
	virtual const type_info& GetClassInfo();
};

