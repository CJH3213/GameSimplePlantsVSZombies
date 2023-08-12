#include "LawnMowerScript.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "SceneBase.h"
using namespace std::placeholders;

void LawnMowerScript::Awake()
{
	// 获取场景音频脚本
	mAudio = GetScene()->FindGameObject("AdventureAudio")->GetComponent<AudioSource>();

	// 添加动作组
	Vector2 originPos = GetTransform()->GetPosition();
	Vector2 parkingPos = originPos + Vector2(74, 0);
	Vector2 endPos = parkingPos + Vector2(780, 0);
	mAnim->AddKeyframe("Entry", {
		{0.0f, originPos},
		{1.0f, parkingPos}
	});
	mAnim->AddKeyframe("GoOn", {
		{0.0f, parkingPos},
		{3.0f, endPos, 0.0f, Vector2(1, 1),[this]{
			Destroy(mGameObject); }
		}
	});

	// 播放除草机入场动作
	mAnim->Play("Entry");

	// 注册碰撞事件监听
	mCollider->mEnterEvents.AddListener("Enter", std::bind(&LawnMowerScript::CollisionEnter, this, _1));
}

void LawnMowerScript::Update()
{
}

void LawnMowerScript::CollisionEnter(ICollider* other)
{
	if (mIsUsed == false &&
		other->GetGameObj()->mTag == "Zombie")
	{
		mIsUsed = true;
		mAnim->Play("GoOn");
		mAudio->Play("Resource/Sounds/lawnmower.wav");
	}
}
