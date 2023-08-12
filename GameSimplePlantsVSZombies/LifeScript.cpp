#include "LifeScript.h"
#include "TransformComponent.h"
#include <SDL_log.h>
#include "TurfScript.h"

ComponentBase* LifeScript::Clone() const
{
	return new LifeScript(*this);
}

void LifeScript::SetRange(float min, float max)
{
	mMinHP = min;
	mMaxHP = max;
}

void LifeScript::AddHP(float f)
{
	mHP += f;

	SetHp(mHP);
}

void LifeScript::SetHp(float f)
{
	mHP = Math::Clamp(f, mMinHP, mMaxHP);

	mChangeEvents.InvokeAll(mHP);
}

//void LifeScript::ChangeHandle()
//{
//	SDL_Log("Plant HP: %f", mHP);
//	// 默认的血量变动回调，为0死亡
//	if (mHP <= 0.0f)
//	{
//		// 不要直接删除植物，请通过草皮删除植物
//		// 因为草皮管理着其上的多个植物，
//		// 如果直接删除植物，会导致草皮无法种植新植物
//
//		// 获取父对象：草皮
//		GameObject* turf = GetTransform()->mParentTrans->GetGameObject();
//		// 执行草皮块的删除植物方法
//		TurfScript* script = turf->GetComponent<TurfScript>();
//		script->DestroyPlant();
//	}
//}
