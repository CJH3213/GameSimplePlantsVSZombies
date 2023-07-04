#include "TurfScript.h"
#include "GameObject.h"
#include "SceneBase.h"
#include "GrowPlantScript.h"
#include "TextureRender.h"
#include "Game.h"
#include "Input.h"
#include "Peashooter.h"
#include "LifeScript.h"

ComponentBase* TurfScript::Clone() const
{
	TurfScript* newComp = new TurfScript();

	// 植物管理器在组件初始化时候获取，
	// 按钮组件是通过外部注入，一般通过预制件实例化时注入
	// 有可能还是会有bug，注意一下

	return newComp;
}

void TurfScript::Awake()
{
	// 获取卡片银行脚本
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();

	// 获取植物管理器
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// 注册点击监听
	//std::string tag = mGameObject->GetName();
	mBtn->mMouseEnterEvents.AddListener("Enter", std::bind(&TurfScript::OnMouseEnter, this));
	mBtn->mMouseOverEvents.AddListener("Over", std::bind(&TurfScript::OnMouseOver, this));
	mBtn->mMouseExitEvents.AddListener("Exit", std::bind(&TurfScript::OnMouseExit, this));
	mBtn->OnClick.AddListener("OnClick", std::bind(&TurfScript::OnClick, this));
}

void TurfScript::DestroyPlant()
{
	//销毁目前草皮上的植物（及其子对象）
	DestroyAllChildren(mPlant);
	Destroy(mPlant);
	mPlant = nullptr;
}

void TurfScript::OnMouseEnter()
{
	GameObject* obj = mPlantManager->mMouseHold;
	// 如果鼠标持有植物，并且鼠标移入草皮，显示种植效果
	if(obj != nullptr && obj->mName == "PreviewPlant" && mPlant == nullptr)
	{
		// 鼠标移入草皮，显示半透明的种植效果示意图
		mPreviewPlant = new GameObject(*obj);// ("TurfPlant");
		GetScene()->AddGameObject(mPreviewPlant);
		mPreviewPlant->SetParent(mGameObject);
		mPreviewPlant->mTransform->localPosition = { 0, 0 };
		// 拷贝预种植对象的纹理图片
		TextureRender* textureRender = mPreviewPlant->GetComponent<TextureRender>(); 
		textureRender->SetAlpha(0.6f);
		textureRender->SetDrawOrder(5);
		// 设置脚本参数：标记是种植的不要跟随鼠标移动
		mPreviewPlant->GetComponent<GrowPlantScript>()->mIsPlanted = true;
	}
}

void TurfScript::OnMouseOver()
{
	// 这里这么写有点蠢，不过我还没想到其他方法
	// 悬空在草皮上，且右键按下，取消示意图
	if (Input::GetMouseButton(1) && mPreviewPlant)
	{
		Destroy(mPreviewPlant);
		mPreviewPlant = nullptr;
	}
}

void TurfScript::OnMouseExit()
{
	// 鼠标移出草皮，删除示意效果图
	Destroy(mPreviewPlant);
	mPreviewPlant = nullptr;
}

void TurfScript::OnClick()
{
	// 用预览植物点击，将预览植物种植到草皮上
	if (mPreviewPlant != nullptr && mPlant == nullptr)
	{
		// 实例化预览植物的实际植物
		GrowPlantScript* script = mPreviewPlant->GetComponent<GrowPlantScript>();
		Prefab* plant = script->mPlantInfo.mPlantPrefab;

		// 拷贝-实例化植物预制件
		Prefab* currPlant = new Prefab(*plant);
		mPlant = currPlant;
		GetScene()->AddGameObject(currPlant);
		currPlant->SetParent(mGameObject);	// 注意草块是植物的父对象
		//currPlant->mTransform->localPosition = { 0, 0 };

		// 通知卡片银行（卡槽）种植事件 
		mCardBank->Planted(script->mPlantInfo.mName);

		// 销毁预览种植效果的对象
		Destroy(mPreviewPlant);
		mPreviewPlant = nullptr;
	}
	else
	{
		// 如果是用铁铲点击
		GameObject* obj = mPlantManager->mMouseHold;
		if (obj != nullptr && obj->mName == "Shovel")
		{
			//销毁目前草皮上的植物（及其子对象）
			DestroyPlant();
		}
	}
}
