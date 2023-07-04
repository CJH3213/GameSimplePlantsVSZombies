#pragma once
#include "TextureRender.h"
#include "FontManager.h"

class TextComponent :
    public TextureRender
{
private:
    // ������ʽ
    FontStyle mStyle;
    // �ı�����
    std::wstring mContent;

public:
    // ���캯��
    TextComponent(std::wstring text, const FontStyle& style);
    // ��������
    ~TextComponent();
    // ���
    virtual ComponentBase* Clone() const override;

    // �����ʼ��
    virtual void Awake() override;

    // �����ı�����
    void SetContent(std::wstring str);
    // ����������ʽ
    void SetStyle(FontStyle& style);
    // ͬʱ�������ݺ���ʽ
    void Set(std::wstring str, FontStyle& style);

    // ������������
    void Regenerate();
};

