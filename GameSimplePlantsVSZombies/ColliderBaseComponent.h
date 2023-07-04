#pragma once
#include "ComponentBase.h"
#include "IRenderer.h"
#include "ICollider.h"
#include <functional>
#include "Rectangle.h"
#include <map>


class ColliderBaseComponent :
    public ComponentBase, ICollider, IRenderer
{
private:
    // 碰撞前后帧状态
    struct CollisionInfo
    {
        bool mPrevState = false;
        bool mCurrState = false;
    };

    // 记录相交碰撞器上次碰撞状态
    std::map<ICollider*, CollisionInfo> mRecords;
    // 记录与鼠标的碰撞状态
    CollisionInfo mMouseHover = { false, false };
    CollisionInfo mMouseClick = { false, false };

public:
    //是否为触发器，触发器可以穿透而碰撞箱不能穿透
    bool isTrigger = false;
    //包围盒
    Rectangle mBounds;

    //构造
    ColliderBaseComponent(std::string name);
    //析构
    virtual ~ColliderBaseComponent();

    //初始化
    virtual void Awake() override;

    /******************渲染接口实现******************/
    // 绘制包围盒
    virtual void OnRender(Window* w) override;

    /******************碰撞接口实现******************/
    // 碰撞检测结束后调用
    virtual void LateCollideUpdate() override;
    // 碰撞回调函数
    virtual void OnCollisionCallback(ICollider*) override;

    // 初次相交回调
    virtual void OnCollisionEnter(ICollider*)  override {};
    // 持续相交回调
    virtual void OnCollisionStay(ICollider*)  override {};
    // 结束相交回调
    virtual void OnCollisionExit(ICollider*)  override {};

    // 获取碰撞器所挂载的游戏对象
    virtual class GameObject* GetGameObj() override;
    // 获取当前碰撞器的包围盒
    virtual Rectangle& GetBounds() override;
    // 检查是否与另一个碰撞器相交
    virtual bool IsIntersectWithAABB(Rectangle&) override;
};

///*碰撞算法*/
////检测点与点是否重合
//static bool CheckPointWithPoint(Vector2& point1, Vector2& point2);
//
////检测圆形与圆形是否碰撞
//static bool CheckCircleWithCircle(class CircleColliderComponent* circle1, class CircleColliderComponent* circle2);
////检测圆形与点是否碰撞
//static bool CheckCircleWithPoint(class CircleColliderComponent* circle, Vector2& point);
//
////检测箱体与箱体是否碰撞
//static bool CheckBoxWithBox(class BoxColliderComponent* box1, BoxColliderComponent* box2);
////检测箱体与点是否碰撞
//static bool CheckBoxWithPoint(class BoxColliderComponent* box, Vector2& point);
////检测箱体与圆形是否碰撞
//static bool CheckBoxWithCircle(class BoxColliderComponent* box, class CircleColliderComponent* circle);
