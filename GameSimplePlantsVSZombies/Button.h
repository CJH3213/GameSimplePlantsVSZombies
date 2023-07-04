#pragma once
#include "ComponentBase.h"
#include "IPointer.h"
#include "IRenderer.h"
#include "EventHandlers.h"
#include "Vector2.h"

class Button :
    public ComponentBase, public IPointer, public IRenderer
{
protected:
    // 记录鼠标状态
    bool mMouseHover[2] = { false, false };
    bool mMouseClick[2] = { false, false };

public:
    // 碰撞盒大小
    Vector2 mSize = { 10, 10 };
    // 基坐标偏移
    Vector2 mOffset;

    // 析构函数
    ~Button();
    // 深拷贝
    virtual ComponentBase* Clone() const override;

    // 组件初始化
    virtual void Awake() override;

    // 获取当前碰撞器的包围盒
    Rectangle GetBounds();

    /******************鼠标碰撞接口实现******************/
        // 鼠标 回调
    virtual void OnMouseCallback(Vector2 pos) override;
    // 鼠标检测结束后调用
    virtual void LateMouseUpdate(Vector2 pos) override;

    // 获取碰撞器所挂载的游戏对象
    virtual class GameObject* GetGameObj() override;
    // 检查是否与另一个碰撞器相交
    virtual bool IsIntersectWithPoint(const Vector2& pos) override;

    // 鼠标悬浮在碰撞器上方的第一帧（非点击）
    EventHandlers<void()> mMouseEnterEvents;
    // 鼠标持续悬浮在碰撞器上每一帧（非点击）
    EventHandlers<void()> mMouseOverEvents;
    // 鼠标悬浮移出碰撞器时最后一帧（非点击）
    EventHandlers<void()> mMouseExitEvents;
    // 鼠标点击碰撞器的第一帧（点击）
    EventHandlers<void()> mMouseDownEvents;
    // 鼠标点击碰撞器的第一帧（点击）
    EventHandlers<void()> mMouseDragEvents;
    // 鼠标点击碰撞器的第一帧（点击）
    EventHandlers<void()> mMouseUpEvents;
    // 鼠标点击和释放都在按键上（点击）
    EventHandlers<void()> mMouseUpAsButtonEvents;
    EventHandlers<void()>& OnClick = mMouseUpAsButtonEvents;

    /******************渲染接口实现******************/
    virtual bool IsRenderEnable() override{ return IsEnable(); }
    virtual void OnRender(Window* w) override;
};

