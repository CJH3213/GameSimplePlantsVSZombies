#pragma once
#include "Button.h"
#include "Texture.h"

class ImageButton :
    public Button
{
protected:
    // 按钮普通图片
    std::string mNormalImgPath;
    Texture* mNormalTex = nullptr;
    // 按钮高光图片
    std::string mHighLigImgPath;
    Texture* mHighLigTex = nullptr;
    // 按钮按压图片
    std::string mPressedImgPath;
    Texture* mPressedTex = nullptr;
    // 待渲染目标纹理
    Texture* mRenderTex = nullptr;

public:

    // 构造函数
    ImageButton(
        std::string normalPath, 
        std::string highLigPath, 
        std::string pressedPath);
    // 析构函数
    ~ImageButton();
    // 深拷贝
    virtual ComponentBase* Clone() const override;

    // 组件初始化
    virtual void Awake() override;
    // 组件更新
    virtual void Update() override;

    // 鼠标进入回调
    void OnMouseEnter();
    // 鼠标离开回调
    void OnMouseExit();
    // 鼠标按下回调
    void OnMouseDown();
    // 点击结束回调
    void OnClickDown();


    /******************渲染接口实现******************/
    virtual void OnRender(Window* w) override;
};

