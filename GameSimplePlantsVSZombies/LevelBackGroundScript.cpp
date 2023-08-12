#include "LevelBackGroundScript.h"
#include "SceneBase.h"
#include"Game.h"
#include "GameObject.h"
#include "Animator.h"
#include "Button.h"
#include "Turf.h"
#include "SunCreatorScript.h"
#include "FlagMeter.h"
#include "LawnMower.h"

void LevelBackGroundScript::Awake()
{
	// 获取窗口大小
	Vector2 windowSize = GetScene()->GetGame()->mWindow->GetSize();

	auto animBackGround = mGameObject->GetComponent<Animator>();
	auto animBank = GetScene()->FindGameObject("CardBank")->GetComponent<Animator>();
	auto animChooser = GetScene()->FindGameObject("ChooseBox")->GetComponent<Animator>();

	// 最左侧坐标
	Vector2 leftPos1 = { 700, windowSize.y / 2 };
	// 最右侧坐标
	Vector2 rightPos = { 100, windowSize.y / 2 };
	// 开始对战后的左侧坐标
	Vector2 leftPos2 = { 500, windowSize.y / 2 };
	// 左侧停留5秒，移动至右侧
	animBackGround->AddKeyframe("StayOnLeft", {
	{0.0f, leftPos1},
	{1.0f, leftPos1, 0.0f, {1.0f, 1.0f},
		[this, animBackGround] {animBackGround->Play("GoToRight"); }},
		});
	// 背景图移动至最右侧，唤出卡槽和卡池
	animBackGround->AddKeyframe("GoToRight", {
		{0.0f, leftPos1},
		{1.0f, rightPos, 0.0f, {1.0f, 1.0f},
			[this, animBank,animChooser] {
			animBank->Play("Entry1"); animChooser->Play("Entry"); }},
		});
	// 背景图移动至最左侧，唤出卡槽
	animBackGround->AddKeyframe("GoToLeft", {
		{0.0f, rightPos},
		{1.0f, leftPos2, 0.0f, {1.0f, 1.0f},
			[this, animBank] {
			animBank->Play("Entry2"); 
			InstantiateCollider();}},
		});

	animBackGround->Play("StayOnLeft");

}

void LevelBackGroundScript::InstantiateCollider()
{
	Vector2 firstTurfPos = { -405, -175 };
	Vector2 turfSize = { 80, 100 };
	Vector2 pos = firstTurfPos;
	int index = 0;

	for(int y = 0; y < 5; y ++)
	{
		for (int x = 0; x < 9; x++)
		{
			Turf* turf = new Turf();
			GetScene()->AddGameObject(turf);
			turf->SetParent(mGameObject);
			turf->mTransform->localPosition = pos;

			turf->mName =  "TurfCollider_" + std::to_string(index);

			index++;
			pos.x += turfSize.x;
		}
		pos.y += turfSize.y;
		pos.x = firstTurfPos.x;
	}

	// 添加除草机
	pos = firstTurfPos;
	pos.x -= 75*2;
	for (int y = 0; y < 5; y++)
	{
		LawnMower* lawnMower = new LawnMower();
		GetScene()->AddGameObject(lawnMower);
		lawnMower->SetParent(mGameObject);
		lawnMower->mTransform->localPosition = pos;
		pos.y += turfSize.y;
	}

	// 添加自然掉落阳光脚本
	SunCreatorScript* creator = new SunCreatorScript();
	mGameObject->AddComponent(creator);
	// 太阳随机生成范围（暂时先硬编码）
	creator->mGrassTLPos = { 56, 76 };
	creator->mGrassBRPos = { 775, 575 };

}
