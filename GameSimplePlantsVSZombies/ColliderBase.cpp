#include "ColliderBase.h"
#include "Game.h"
#include "CollisionManager.h"

ColliderBase::~ColliderBase()
{
    //SDL_Log("Destroy %x", this);
    //for (auto& state : mCollisionState)
    //{
    //    SDL_Log("   ---  %x", state.first);
    //}

    // 处理与之关联的每个碰撞器
    OnDisable();

    // 将当前组件与碰撞管理器分离
    GetGame()->mCollisionManager->RemoveCollider(this);
    // 将当前组件与渲染管理器分离
    GetGame()->mRenderManager->RemoveComponent(this);
}

void ColliderBase::Awake()
{
    // 将当前组件添加到碰撞管理器
    GetGame()->mCollisionManager->AddCollider(this);
    // 将渲染组件添加到渲染管理器
    GetGame()->mRenderManager->AddComponent(this);
}

void ColliderBase::OnDisable()
{
    // 注意禁用碰撞组件后碰撞状态容器会清空
    // 请勿在碰撞回调里禁用碰撞组件影响遍历

    // 处理与之关联的每个碰撞器
    for (auto& state : mCollisionState)
    {
        if (state.second[0] == false && state.second[1] == false);
        else
        {
            ColliderBase* other = dynamic_cast<ColliderBase*>(state.first);
            other->RemoveColliderRecord(this);
        }
    }
    mCollisionState.clear();
}

void ColliderBase::RemoveColliderRecord(ICollider* other)
{
    auto iter = mCollisionState.find(other);
    if (iter != mCollisionState.end())
    {
        //SDL_Log("%x --- %x", this, other);
        //mCollisionState.erase(iter);
        (*iter).second = { false, false };
    }
}

void ColliderBase::OnCollisionCallback(ICollider* other)
{
    //SDL_Log("Collision %s", mGameObject->mTag.c_str());
    auto iter = mCollisionState.find(other);
    if (iter == mCollisionState.end())
        mCollisionState.emplace(other, std::array<bool, 2>{false, true});
    else
        (*iter).second[1] = true;
}

void ColliderBase::LateCollideUpdate()
{

    // 根据前后两帧的状态调用对应的回调函数
    for (auto it = mCollisionState.begin(); it != mCollisionState.end();)
    {
        if ((*it).second[0] == false)
        {
            if ((*it).second[1] == false)  // 0 0 碰撞关系已结束，销毁记录
            {
                it = mCollisionState.erase(it);
                continue;
            }
            else  // 0 1 初次碰撞
                mEnterEvents.InvokeAll((*it).first);
        }
        else
        {
            if ((*it).second[1] == true)    // 1 1 持续碰撞
                mStayEvents.InvokeAll((*it).first);
            else    // 1 0 结束碰撞
                mExitEvents.InvokeAll((*it).first);
        }

       // 为下次遍历准备状态
        if(it != mCollisionState.end())
        {
            (*it).second[0] = (*it).second[1];
            (*it).second[1] = false;

            it++;
        }
    }

}

GameObject* ColliderBase::GetGameObj()
{
    return mGameObject;
}

void ColliderBase::OnRender(Window* w)
{
    // 绘制包围盒
    w->SetPenColor(255, 255, 0, 0);
    w->DrawRectangle(GetBounds());
}
