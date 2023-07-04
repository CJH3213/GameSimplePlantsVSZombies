#pragma once
#include "ImageButton.h"
#include "FontManager.h"

class TextButton :
    public ImageButton
{
private:
    // 字体样式（默认）
    FontStyle mNormalStyle;
    // 字体样式（鼠标悬停，高光）
    FontStyle mHighLigStyle;

    // 文本内容
    std::wstring mContent;

public:
    // 构造函数
    TextButton(std::wstring text,
        FontStyle normalSty, FontStyle highLigSty);
    // 应该不用写析构吧

    // 组件初始化
    virtual void Awake();
};

