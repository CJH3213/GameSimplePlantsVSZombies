#pragma once
#include "SceneBase.h"

class LoadingPageScene :
    public SceneBase
{
private:

public:
    LoadingPageScene(std::string name);

    // �������غ�ʵ��������
    virtual void Start() override;

};

/*
    ����ҳ�漰��ӭ���棬����Ϊһ�ű���ͼ���·��ļ��ؽ�������
    �������Բݾ��̿�����ʽ����һ�ž��β�Ƥ�����һ��Բ�βݾ��ɣ�
    �ݾ�ʼ�ձ����ڲ�Ƥ�����Ҷˣ��ݾ����̶�����ʾ����Ϊ���ȱ�����ͬʱ�ݾ���ת�Ƕ�Ҳ�ͽ����йء�
*/

