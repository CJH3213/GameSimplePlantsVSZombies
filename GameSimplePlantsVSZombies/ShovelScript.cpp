#include "ShovelScript.h"
#include "Input.h"
#include "TransformComponent.h"
#include "SceneBase.h"

void ShovelScript::Awake()
{
	// 获取植物管理器
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// 注册点击监听事件
	mBtn->OnClick.AddListener("OnClick", std::bind(&ShovelScript::OnClick, this));
}

void ShovelScript::Update()
{

	if (mIsUsing && Input::GetMouseButton(1))
	{
		// 使用中如果按下右键，铲子归位
			mIsUsing = false;
			GetTransform()->localPosition = { 0, 0 };
			mPlantManager->mMouseHold = nullptr;
	}

	if(mIsUsing)
	{
		// 让对象附着在鼠标坐标上
		GetTransform()->SetPosition(Input::GetMousePosition());
	}
}

void ShovelScript::OnClick()
{
	if (mIsUsing == false)
	{
		if(mPlantManager->mMouseHold == nullptr)
		{
			mPlantManager->mMouseHold = mGameObject;
			mIsUsing = true;
		}
	}
}
