#include "ProjectilePeaScript.h"
#include "Time.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "LifeScript.h"
using namespace std::placeholders;

ComponentBase* ProjectilePeaScript::Clone() const
{
    return new ProjectilePeaScript(*this);
}

void ProjectilePeaScript::Awake()
{
    // ��ȡ��ײ���
    mCollider = mGameObject->GetComponent<BoxCollider>();
    // ��Ӽ����¼�
    mCollider->mEnterEvents.AddListener("Enter", std::bind(&ProjectilePeaScript::CollisionEnter, this, _1));

    mLastTime = Time::Time_s();
}

void ProjectilePeaScript::Update()
{
    float deltaTime = Time::Time_s() - mLastTime;
    mLastTime = Time::Time_s();

    GetTransform()->localPosition.x += deltaTime * mSpeed;

    // �ɳ���Ļ�����ٵ�
    if (GetTransform()->GetPosition().x > 800)
    {
        Destroy(mGameObject);
    }
}

void ProjectilePeaScript::CollisionEnter(ICollider* other)
{
    if(other->GetGameObj()->mTag == "Zombie")
    {
        other->GetGameObj()->GetComponent<LifeScript>()->
            AddHP(-mDamage);

        Destroy(mGameObject);
    }
}
