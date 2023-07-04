#include "SunCreatorScript.h"
#include "Time.h"
#include "Random.h"
#include "Sun.h"
#include "SunScript.h"
#include "SceneBase.h"
#include "Animator.h"

void SunCreatorScript::Awake()
{
	mNextTime = Time::Time_s() + Random(5.0f, 10.0f);
}

void SunCreatorScript::Update()
{
	if (Time::Time_s() >= mNextTime)
	{
		mNextTime = Time::Time_s() + Random(5.0f, 10.0f);

		Prefab* sun = new Sun();
		GetScene()->AddGameObject(sun);
		sun->SetParent(mGameObject);
		sun->mTransform->localPosition.x = Random(-20.0f, 20.0f);
		// ������ɵ���С̫��
		sun->GetComponent<SunScript>()->SetIsBigSun(true);

		// ����������ʼ���ն�����
		Vector2 grassTLPos = mGrassTLPos;//{ 56, 76 };	//�ݵ����Ͻ�
		Vector2 grassBRPos = mGrassBRPos;//{ 775, 575 };	//�ݵ����½�
		Vector2 beginPos = { Random(grassTLPos.x, grassBRPos.x), Random(grassTLPos.y, grassBRPos.y) };
		Vector2 endPos = {beginPos.x, Random(beginPos.y, grassBRPos.y)};
		float endTime = (endPos.y - beginPos.y) / 100.0f;	// ʱ��=·��/�ٶ�
		// �˶�����������
		Animator* anim = sun->GetComponent<Animator>();
		anim->AddKeyframe("Drop", {
			{0.0f, beginPos, 0.0f, sun->mTransform->localScale},
			{endTime, endPos, 0.0f, sun->mTransform->localScale}
			});
		anim->Play("Drop");
	}
}
