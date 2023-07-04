#pragma once
#include <vector>
#include "GameObject.h"
#include "Prefab.h"

/// <summary>
/// 场景（基类）；
/// 容纳当前关卡、场景中所有游戏对象；
/// </summary>
class SceneBase    //并不想继承自GameObject
    : public Object   //场景的上级到底是管理器还是Game呢？
{
private:
    // 场景名称
    std::string mName;

public:
    // 游戏对象
    class Game* mGame = nullptr;
    // 正在执行逻辑更新标志
    bool mIsUpdating = false;
    // 已生效游戏对象容器
    std::vector<GameObject*> mGameObjects;
    // 悬而未决的游戏对象容器
    std::vector<GameObject*> mPendingGameObjects;

    // 构造函数
    SceneBase(std::string name);
    // 析构函数
    ~SceneBase();

    // 获取场景名
    std::string GetName() const { return mName; };

    // 添加游戏对象
    void AddGameObject(GameObject* gObj);
    // 添加预制件对象
    void AddGameObject(Prefab* gObj);
    // 添加多个游戏对象
    template<typename T>
    void AddGameObjects(const T& gObjs);
    // 移除游戏对象
    void RemoveGameObject(GameObject* gObj);
    // 通过名字查找对象
    GameObject* FindGameObject(std::string name);

    //暂停场景
    void Paused();

    // 场景加载和实例化对象
    virtual void Start() {};

    // 获取游戏对象
    class Game* GetGame() { return mGame; }

};

template<typename T>
inline void SceneBase::AddGameObjects(const T& gObjs)
{
    for (auto& obj : gObjs)
        AddGameObject(obj);
}
