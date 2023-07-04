#include "SunflowerScript.h"
#include "Time.h"
#include "Sun.h"
#include "SceneBase.h"
#include "Random.h"
#include "SunScript.h"
#include "LifeScript.h"
#include "TurfScript.h"
using namespace std::placeholders;

ComponentBase* SunflowerScript::Clone() const
{
	return new SunflowerScript(*this);
}

void SunflowerScript::Awake()
{
	// ��ȡֲ�������
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// ��������ֵ�仯�¼�
	mGameObject->GetComponent<LifeScript>()->mChangeEvents.
		AddListener("HPChange", std::bind(&SunflowerScript::HPChange, this, _1));

	// ���տ��״β�����ʱ�����3S~13S�����ֵ
	mNextTime = Time::Time_s() + Random(3.0f, 13.0f);
}

void SunflowerScript::Update()
{
	if (Time::Time_s() >= mNextTime)
	{
		mNextTime += mInterval;

		Prefab* sun = new Sun();
		GetScene()->AddGameObject(sun);
		sun->SetParent(mGameObject);
		sun->mTransform->localPosition.x = Random(-20.0f, 20.0f);
		// ������ɵ���С̫��
		sun->GetComponent<SunScript>()->SetIsBigSun(false);
	}
}

void SunflowerScript::HPChange(float hp)
{
	SDL_Log("Sunflower HP: %f", hp);
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
