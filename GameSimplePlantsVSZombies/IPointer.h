#pragma once
#include "Vector2.h"
#include "ICollider.h"

class IPointer
{
public:
    // 鼠标 回调
    virtual void OnMouseCallback(Vector2) = 0;
    // 鼠标检测结束后调用
    virtual void LateMouseUpdate(Vector2)  = 0;

    //// 鼠标悬浮在碰撞器上方的第一帧（非点击）
    //virtual void OnMouseEnter(Vector2) {};
    //// 鼠标持续悬浮在碰撞器上每一帧（非点击）
    //virtual void OnMouseOver(Vector2) {};
    //// 鼠标悬浮移出碰撞器时最后一帧（非点击）
    //virtual void OnMouseExit(Vector2) {};
    //// 鼠标点击碰撞器的第一帧（点击）
    //virtual void OnMouseDown(Vector2) {};
    //// 鼠标点击碰撞器的第一帧（点击）
    //virtual void OnMouseDrag(Vector2) {};
    //// 鼠标点击碰撞器的第一帧（点击）
    //virtual void OnMouseUp(Vector2) {};
    //// 鼠标点击和释放都在按键上（点击）
    //virtual void OnMouseUpAsButton(Vector2) {};

    // 获取碰撞器所挂载的游戏对象
    virtual class GameObject* GetGameObj() = 0;
    // 检查是否与另一个碰撞器相交
    virtual bool IsIntersectWithPoint(const Vector2&) = 0;
};

