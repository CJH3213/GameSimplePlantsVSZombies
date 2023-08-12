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

    // ������֮������ÿ����ײ��
    OnDisable();

    // ����ǰ�������ײ����������
    GetGame()->mCollisionManager->RemoveCollider(this);
    // ����ǰ�������Ⱦ����������
    GetGame()->mRenderManager->RemoveComponent(this);
}

void ColliderBase::Awake()
{
    // ����ǰ�����ӵ���ײ������
    GetGame()->mCollisionManager->AddCollider(this);
    // ����Ⱦ�����ӵ���Ⱦ������
    GetGame()->mRenderManager->AddComponent(this);
}

void ColliderBase::OnDisable()
{
    // ע�������ײ�������ײ״̬���������
    // ��������ײ�ص��������ײ���Ӱ�����

    // ������֮������ÿ����ײ��
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

    // ����ǰ����֡��״̬���ö�Ӧ�Ļص�����
    for (auto it = mCollisionState.begin(); it != mCollisionState.end();)
    {
        if ((*it).second[0] == false)
        {
            if ((*it).second[1] == false)  // 0 0 ��ײ��ϵ�ѽ��������ټ�¼
            {
                it = mCollisionState.erase(it);
                continue;
            }
            else  // 0 1 ������ײ
                mEnterEvents.InvokeAll((*it).first);
        }
        else
        {
            if ((*it).second[1] == true)    // 1 1 ������ײ
                mStayEvents.InvokeAll((*it).first);
            else    // 1 0 ������ײ
                mExitEvents.InvokeAll((*it).first);
        }

       // Ϊ�´α���׼��״̬
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
    // ���ư�Χ��
    w->SetPenColor(255, 255, 0, 0);
    w->DrawRectangle(GetBounds());
}
