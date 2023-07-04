#include "PeashooterScript.h"
#include "Time.h"
#include "ProjectilePea.h"
#include "SceneBase.h"
#include "LifeScript.h"
#include "TurfScript.h"
using namespace std::placeholders;

void PeashooterScript::CreateDetector()
{
    // ������ʬ̽����
    GameObject* detector = new GameObject("Detector");
    GetScene()->AddGameObject(detector);
    detector->SetParent(mGameObject);
    // ̽��������ײ��
    BoxCollider* collider = new BoxCollider();
    detector->AddComponent(collider);
    // ��Χ�Ǵ�ֲ�ﵽ��Ļ�Ҳ�
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
    // ��ȡ����ͼƬ��ɫ
    mBackGround = GetScene()->FindGameObject("BackGround");

    // ��������ֵ�仯�¼�
    mGameObject->GetComponent<LifeScript>()->mChangeEvents.
        AddListener("HPChange", std::bind(&PeashooterScript::HPChange, this, _1));

    // ������ʬ̽����
    CreateDetector();

    // ��һ���㶹�ķ���ʱ��
    //mNextTime = Time::Time_s() + mInterval;
}

void PeashooterScript::Update()
{
    // ���û�н�ʬ��ÿ֡�����´�һ��
    if(GetZombiesNum() == 0)
        mNextTime = Time::Time_s() + mInterval;
    // ������ڽ�ʬ�����Ҵﵽ������������һ���ӵ�
    else if (mNextTime < Time::Time_s())
    {
        mNextTime += mInterval;

        // ����һ���㶹
        ProjectilePea* pea = new ProjectilePea();
        GetScene()->AddGameObject(pea);
        pea->SetParent(mBackGround);    //�㶹�������㶹�ĵ����������ܴ�����
        // �䶨�㶹��ʼ���������ֵ��첿
        pea->mTransform->SetPosition(GetTransform()->GetPosition() + Vector2(29, -23));
    }
}

void PeashooterScript::HPChange(float hp)
{
    SDL_Log("Peashooter HP: %f", hp);
    // Ĭ�ϵ�Ѫ���䶯�ص���Ϊ0����
    if (hp <= 0.0f)
    {
        // ��Ҫֱ��ɾ��ֲ���ͨ����Ƥɾ��ֲ��
        // ��Ϊ��Ƥ���������ϵĶ��ֲ�
        // ���ֱ��ɾ��ֲ��ᵼ�²�Ƥ�޷���ֲ��ֲ��

        // ��ȡ�����󣺲�Ƥ
        GameObject* turf = GetTransform()->mParentTrans->GetGameObject();
        // ִ�в�Ƥ���ɾ��ֲ�﷽��
        TurfScript* script = turf->GetComponent<TurfScript>();
        script->DestroyPlant();
    }
}

