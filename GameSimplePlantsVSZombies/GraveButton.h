#pragma once
#include "ImageButton.h"

class GraveButton :
    public ImageButton
{
private:

public:
    // ���캯��
    GraveButton(
        std::string normalPath,
        std::string highLigPath);

    // �����ʼ��
    virtual void Awake();

    // �������ײ���ĵ�һ֡�������
    void OnMouseDown();
    // �������ײ���ĵ�һ֡�������
    void OnMouseUp();
};

