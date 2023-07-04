#include "PeashooterScript.h"
#include "Time.h"
#include "ProjectilePea.h"
#include "SceneBase.h"
#include "LifeScript.h"
#include "TurfScript.h"
using namespace std::placeholders;

void PeashooterScript::CreateDetector()
{
    // 创建僵尸探测器
    GameObject* detector = new GameObject("Detector");
    GetScene()->AddGameObject(detector);
    detector->SetParent(mGameObject);
    // 探测器的碰撞器
    BoxCollider* collider = new BoxCollider();
    detector->AddComponent(collider);
    // 范围是从植物到屏幕右侧
    collider->mSize = { 800 - GetTransform()->GetPosition().x, 5 };
    collider->mOffset.x = collider->mSize.x / 2;

    mDetectorCollider = collider;
}

size_t PeashooterScript::GetZombiesNum()
{
    size_t count = 0;

    for (auto& other : mDetectorCollider->GetCollisionState())
    {
        if (other.first->GetGameObj()->mTag == "Zombie")
            count++;
    }
    return count;
}

ComponentBase* PeashooterScript::Clone() const
{
    return new PeashooterScript(*this);
}

void PeashooterScript::Awake()
{
    // 获取背景图片角色
    mBackGround = GetScene()->FindGameObject("BackGround");

    // 监听生命值变化事件
    mGameObject->GetComponent<LifeScript>()->mChangeEvents.
        AddListener("HPChange", std::bind(&PeashooterScript::HPChange, this, _1));

    // 创建僵尸探测器
    CreateDetector();

    // 第一颗豌豆的发射时间
    //mNextTime = Time::Time_s() + mInterval;
}

void PeashooterScript::Update()
{
    // 如果没有僵尸，每帧都是下次一定
    if(GetZombiesNum() == 0)
        mNextTime = Time::Time_s() + mInterval;
    // 如果存在僵尸，并且达到发射间隔，发射一颗子弹
    else if (mNextTime < Time::Time_s())
    {
        mNextTime += mInterval;

        // 发射一颗豌豆
        ProjectilePea* pea = new ProjectilePea();
        GetScene()->AddGameObject(pea);
        pea->SetParent(mBackGround);    //豌豆射手是豌豆的爹，但背景能存活更久
        // 射定豌豆初始坐标在射手的嘴部
        pea->mTransform->SetPosition(GetTransform()->GetPosition() + Vector2(29, -23));
    }
}

void PeashooterScript::HPChange(float hp)
{
    SDL_Log("Peashooter HP: %f", hp);
    // 默认的血量变动回调，为0死亡
    if (hp <= 0.0f)
    {
        // 不要直接删除植物，请通过草皮删除植物
        // 因为草皮管理着其上的多个植物，
        // 如果直接删除植物，会导致草皮无法种植新植物

        // 获取父对象：草皮
        GameObject* turf = GetTransform()->mParentTrans->GetGameObject();
        // 执行草皮块的删除植物方法
        TurfScript* script = turf->GetComponent<TurfScript>();
        script->DestroyPlant();
    }
}

