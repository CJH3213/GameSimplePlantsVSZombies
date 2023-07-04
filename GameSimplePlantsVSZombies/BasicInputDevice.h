#pragma once
#include <typeinfo>

class BasicInputDevice
{
private:

public:
	//��ʼ���͹ر�
	virtual void Initialize() {}
	virtual void Shutdown() {}

	//����ǰ��׼��
	virtual void PrepareForUpdate() {}
	//����
	virtual void Update(){}

	//��ȡ��ǰ����Ϣ
	virtual const type_info& GetClassInfo();
};

