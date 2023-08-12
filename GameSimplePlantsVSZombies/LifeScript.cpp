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
//	// Ĭ�ϵ�Ѫ���䶯�ص���Ϊ0����
//	if (mHP <= 0.0f)
//	{
//		// ��Ҫֱ��ɾ��ֲ���ͨ����Ƥɾ��ֲ��
//		// ��Ϊ��Ƥ���������ϵĶ��ֲ�
//		// ���ֱ��ɾ��ֲ��ᵼ�²�Ƥ�޷���ֲ��ֲ��
//
//		// ��ȡ�����󣺲�Ƥ
//		GameObject* turf = GetTransform()->mParentTrans->GetGameObject();
//		// ִ�в�Ƥ���ɾ��ֲ�﷽��
//		TurfScript* script = turf->GetComponent<TurfScript>();
//		script->DestroyPlant();
//	}
//}
