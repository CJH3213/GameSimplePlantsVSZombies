#pragma once
#include "ComponentBase.h"
#include "IRenderer.h"

class TextureRender :
    public ComponentBase, public IRenderer
{
private:
    // 图像路径
    //std::string mImgPath = "";
    // 绘制层级（值越小离相机越近）
    int mDrawOrder;

public:
    //纹理
    Texture* mTexture = nullptr;
    //偏移
    Vector2 mOffset;

    //构造函数
    TextureRender(Texture* texture, int drawOrder = 100);
    //析构函数
    ~TextureRender();
    // 深拷贝
    virtual ComponentBase* Clone() const override;

    //组件初始化
    virtual void Awake() override;

    // 设置绘制层级（减少动态调整以降低额外开销），不要调用，还有bug没解决
    void SetDrawOrder(int drawOrder);
    // 改变纹理图片
    void ChangeTexture(std::string imgPath);
    void ChangeTexture(Texture* texture);
    // 设置透明通道
    void SetAlpha(float alpha);

    // 是否启用渲染
    virtual bool IsRenderEnable() override { return IsEnable(); }
    // 提供渲染管理器获取渲染深度（绘制顺序）
    virtual int GetDrawOrder() const override;
    // 受渲染器调用的Draw方法
    virtual void OnRender(Window* w) override;
};

