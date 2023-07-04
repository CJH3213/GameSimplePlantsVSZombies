#pragma once
#include "Object.h"

/// <summary>
/// 组件（基类）；
/// 将游戏对象的部分功能封装成一个组件；
/// </summary>
class ComponentBase
     : public Object    //继承权限public它者才能访问成员
{
protected:
    // 自带拷贝和移动
    ComponentBase(const ComponentBase&) = default;
    ComponentBase& operator=(const ComponentBase&) = default;
    ComponentBase(ComponentBase&&) = default;
    ComponentBase& operator=(ComponentBase&&) = default;

protected:
    // 组件使能/禁用
    bool mIsEnable = true;
    // 所插入的游戏对象
    class GameObject* mGameObject = nullptr;

    //标记是否已经执行过Start方法
    bool mIsStarted;

public:
    // 构造函数：设置对象名和持有组件的游戏对象
    ComponentBase();
    // 析构函数：基类的析构函数务必为虚函数
    virtual ~ComponentBase();
    // 手动实现深拷贝
    virtual ComponentBase* Clone() const { return nullptr; }

    // 设置插入的游戏对象（依赖注入）
    void SetOwner(class GameObject* obj);
    // 设置组件活跃/禁用
    void SetEnable(bool b);
    // 获取活跃状态
    bool IsEnable() const { return mIsEnable; }


    /*继承的组件提供基础方法*/
    // 添加到游戏对象后调用一次
    virtual void Awake(){}
    // 第一次调用Update前执行一次
    virtual void Start(){}
    
    // 逻辑更新（受引擎调用，不要重写这个方法）
    void _Update();
    // 逻辑更新后
    virtual void LateUpdate(){}

    // 渲染更新
    virtual void OnRendering(){}

    // 固定间隔更新
    virtual void FixedUpdate(){}

    // 销毁前
    virtual void Destroy(){}


    // 获取Game对象
    class Game* GetGame();
    // 获取场景对象
    class SceneBase* GetScene();
    // 获取组件所在的游戏对象
    class GameObject* GetGameObject() { return mGameObject; }
    // 获取Transform组件
    class TransformComponent* GetTransform();

protected:
    // 逻辑更新（由用户重写）
    virtual void Update() {}
    // 启用、禁用
    virtual void OnEnable(){}
    virtual void OnDisable(){}

    // 实例化预制件
    template<typename T>
    T* Instantiate(T* obj, TransformComponent* parent);
    // 申请销毁游戏对象
    void Destroy(class GameObject* gObj);
    // 销毁所有子对象（不包括当前对象）
    void DestroyAllChildren(class GameObject* gObj);
};

template<typename T>
inline T* ComponentBase::Instantiate(T* obj, TransformComponent* parent)
{
    GetScene()->AddGameObject(obj);		// 将对象添加到当前场景
    obj->mTransform->SetParent(parent);	// 设置父关系

    return obj;
}
