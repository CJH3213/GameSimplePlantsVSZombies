#pragma once
#include "TextureRender.h"
#include "FontManager.h"

class TextComponent :
    public TextureRender
{
private:
    // 字体样式
    FontStyle mStyle;
    // 文本内容
    std::wstring mContent;

public:
    // 构造函数
    TextComponent(std::wstring text, const FontStyle& style);
    // 析构函数
    ~TextComponent();
    // 深拷贝
    virtual ComponentBase* Clone() const override;

    // 组件初始化
    virtual void Awake() override;

    // 设置文本内容
    void SetContent(std::wstring str);
    // 设置字体样式
    void SetStyle(FontStyle& style);
    // 同时设置内容和样式
    void Set(std::wstring str, FontStyle& style);

    // 重新生成纹理
    void Regenerate();
};

