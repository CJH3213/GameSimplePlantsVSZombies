#include "ShovelScript.h"
#include "Input.h"
#include "TransformComponent.h"
#include "SceneBase.h"

void ShovelScript::Awake()
{
	// ��ȡֲ�������
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// ע���������¼�
	mBtn->OnClick.AddListener("OnClick", std::bind(&ShovelScript::OnClick, this));
}

void ShovelScript::Update()
{

	if (mIsUsing && Input::GetMouseButton(1))
	{
		// ʹ������������Ҽ������ӹ�λ
			mIsUsing = false;
			GetTransform()->localPosition = { 0, 0 };
			mPlantManager->mMouseHold = nullptr;
	}

	if(mIsUsing)
	{
		// �ö����������������
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
