#pragma once
#include "ImageButton.h"
#include "FontManager.h"

class TextButton :
    public ImageButton
{
private:
    // ������ʽ��Ĭ�ϣ�
    FontStyle mNormalStyle;
    // ������ʽ�������ͣ���߹⣩
    FontStyle mHighLigStyle;

    // �ı�����
    std::wstring mContent;

public:
    // ���캯��
    TextButton(std::wstring text,
        FontStyle normalSty, FontStyle highLigSty);
    // Ӧ�ò���д������

    // �����ʼ��
    virtual void Awake();
};

