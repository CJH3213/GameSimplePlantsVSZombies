#pragma once
#include "ComponentBase.h"
#include "Vector2.h"
#include <vector>

//坐标空间：自身、世界
enum class Space : uint8_t  {Model, Self, Parent, World};

class TransformComponent :
    public ComponentBase
{
private:
    // 存储所有直属子对象的变换组件
    std::vector<TransformComponent*> mChildren;

public:
    Vector2 localPosition;       //相对坐标
    float localRotation;     //相对角度
    Vector2 localScale;      //相对缩放比
    // 父对象的变换组件
    TransformComponent* mParentTrans = nullptr;

    // 构造函数：全属性设置
    TransformComponent(TransformComponent* parentTrans,
        const Vector2& p, float r, const Vector2& s) ;
    // 构造函数：只指定位置坐标，不旋转（0）不缩放（1,1）
    TransformComponent(TransformComponent* parentTrans);
    // 构造函数：只设置基础组件信息，不设置位置和父对象
    TransformComponent();
    // 析构函数
    ~TransformComponent();
    // 深拷贝
    virtual ComponentBase* Clone() const override;

    // 获取世界位置
    Vector2 GetPosition() const;
    // 设置世界位置
    void SetPosition(Vector2 p);
    // 获取世界旋转角度
    float GetRotation() const;
    // 设置世界旋转角度
    void SetRotation(float r);
    // 获取世界缩放比
    Vector2 GetScale() const;
    // 设置世界缩放比
    void SetScale(Vector2 v);

    // 执行前的准备；场景所有游戏对象实例化后，作为组件的初始化
    //virtual void Start() override;

    // 移动物体
    void Translate(float x, float y, Space relativeTo);
    void Translate(const Vector2& v, Space relativeTo);

    // 旋转物体
    void Rotate(float angle, Space relativeTo);
    void RotateAround(float angle, const Vector2& v);
    bool LookAt(const Vector2& v);

    // 缩放物体
    void Scale(const Vector2& v, Space relativeTo);
    void Scale(float f, Space relativeTo);


    /**********************以下是提供于层级管理的方法**************************/
    // 设置父关系
    void SetParent(TransformComponent* parent);
    // 获取子对象数量
    size_t ChildCount();
    // 获取直属子对象变换组件
    TransformComponent* GetChild(size_t index);
    
};

