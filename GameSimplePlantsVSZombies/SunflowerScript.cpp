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
	// 获取植物管理器
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// 监听生命值变化事件
	mGameObject->GetComponent<LifeScript>()->mChangeEvents.
		AddListener("HPChange", std::bind(&SunflowerScript::HPChange, this, _1));

	// 向日葵首次产阳光时间介于3S~13S的随机值
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
		// 标记生成的是小太阳
		sun->GetComponent<SunScript>()->SetIsBigSun(false);
	}
}

void SunflowerScript::HPChange(float hp)
{
	SDL_Log("Sunflower HP: %f", hp);
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
