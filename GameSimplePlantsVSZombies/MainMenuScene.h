#pragma once
#include "SceneBase.h"

class MainMenuScene :
    public SceneBase
{
private:

public:
    MainMenuScene(std::string name);

    // �������غ�ʵ��������
    virtual void Start() override;
};

/*
��־��
22.02.24��������壨��������ڹ��캯������ӣ����ϼ��������ߣ���ȡ��Դ��Start()������ִ�У�
                 ��Ϊ���캯��������ʵ��������ȫ������ʵ����Ϻ�Ż����Start()��������ʱ�Ͳ����ȡ����ָ�롣
*/
