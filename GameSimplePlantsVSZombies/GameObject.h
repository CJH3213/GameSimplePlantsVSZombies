#pragma once
#include <vector>
#include "TransformComponent.h"

/// <summary>
/// 游戏对象（基类）；
/// </summary>
class GameObject
     :public Object
{
protected:
    // 启用/禁用状态
    bool mIsActive = true;
    //所在的场景
    class SceneBase* mScene = nullptr;
    //当前游戏对象的组件容器（活跃组件）
    std::vector<ComponentBase*> mComponents;
    // 添加到游戏对象但未初始的组件（挂起组件）
    std::vector<ComponentBase*> mPendingComponents;

public:
    // 状态枚举
    enum State
    {
        EActive,    //活跃：更新
        EPaused,    //暂停：不更新
        EDead   //死亡：销毁
    };
    // 角色状态
    State mState;

    // 变换组件（所有游戏对象绑定一个变换组件）
    TransformComponent* mTransform = nullptr;
    // 对象标签
    std::string mTag ;// = "Untagged";
    // 对象名称
    std::string mName ;

    // 构造函数：设置对象名和持有组件的游戏对象
    GameObject(std::string name, std::string tag);
    GameObject(std::string name);
    // 析构函数：基类的析构函数务必为虚函数
    ~GameObject();
    // 深拷贝构造
    GameObject(const GameObject& other);

    // 获取对象名
    std::string GetName() const { return mName; }
    // 设置对象启用/禁用
    void SetActive(bool b);
    // 获取对象活跃状态
    bool GetActive() const { return mIsActive; }

    // 预更新
    virtual void PreUpdate();
    // 逻辑更新
    void Update();
    // 延迟逻辑更新
    void LateUpdate();

    // 设置父对象
    void SetParent(GameObject* obj);
    // 添加（插入）组件到容器中
    void AddComponent(ComponentBase* comp);
    // 从容器中移除指定组件
    void RemoveComponent(ComponentBase* comp);
    // 从容器中移除指定名称的组件
    // void RemoveComponent(std::string name);

    // 设置场景对象
    void SetScene(class SceneBase* s) { mScene = s; }
    // 获取场景对象
    class SceneBase* GetScene(){ return mScene; }
    // 获取游戏对象（游戏上下文）
    class Game* GetGame();

public:
    // 从容器中获取一个指定类型的组件
    template<typename T>
    T* GetComponent();
    // 从对象及其子孙中获取一个指定类型的组件
    template<typename T>
    static T* GetComponentInChildren(TransformComponent* trans);
    // 从对象及其子孙中获取一个指定类型的组件
    template<typename T>
    T* GetComponentInChildren();
};

//模板函数的类型必须在编译期间就确定，所以函数必须放在头文件而不是CPP文件里，函数放在头文件就需要inline内联修饰
//若模板函数的定义放在cpp文件内，编译期间该模板函数只能获取到当前类的类型，其他类的类型是获取不到的。
// 从容器中获取一个指定类型的组件
template<typename T>
T* GameObject::GetComponent()
{
    // 从活跃容器中找组件
    for (auto it = mComponents.begin(); it != mComponents.end(); it++)
    {
        if (typeid(T).name() == (*it)->GetClassInfo().name())
        {
            return dynamic_cast<T*> (*it);  //向下转换类型
        }  
    }
    // 从挂起容器中找组件
    for (auto it = mPendingComponents.begin(); it != mPendingComponents.end(); it++)
    {
        if (typeid(T).name() == (*it)->GetClassInfo().name())
        {
            return dynamic_cast<T*> (*it);  //向下转换类型
        }
    }

    return nullptr;
}

// 从对象及其子孙中获取一个指定类型的组件
template<typename T>
T* GameObject::GetComponentInChildren(TransformComponent* trans)
{
    // 先在当前物体中查找是否有该组件
    T* comp = trans->GetGameObject()->GetComponent<T>();
    if (comp != nullptr)
        return comp;
    // 遍历子物体查找组件
    else
    {
        for (int i = 0; i < trans->ChildCount(); i++)
        {
            T* comp = GetComponentInChildren<T>(trans->GetChild(i));
            if (comp != nullptr)
                return comp;
        }
    }

    return nullptr;
}

// 从对象及其子孙中获取一个指定类型的组件
template<typename T>
T* GameObject::GetComponentInChildren()
{
    return GetComponentInChildren<T>(mTransform);
}