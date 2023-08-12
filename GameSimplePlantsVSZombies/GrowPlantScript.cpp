#include "GrowPlantScript.h"
#include "Input.h"
#include "TransformComponent.h"
#include "SceneBase.h"
#include "TextureRender.h"
#include "Game.h"

ComponentBase* GrowPlantScript::Clone() const
{
	// 直接用拷贝构造把杂七杂八复制进去
	GrowPlantScript* newComp = new GrowPlantScript(*this);

	return newComp;
}

void GrowPlantScript::Awake()
{
	// 获取植物管理器
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// 设置预览角色图
	TextureRender* texRen = mGameObject->GetComponent<TextureRender>();
	if(texRen->mTexture == nullptr)
	{
		texRen->ChangeTexture(GetGame()->mImageManagement->
			GetTexturesByDir(mPlantInfo.mResourceFolder)[0] );
	}
}

void GrowPlantScript::Update()
{
	// 种植到草皮的逻辑代码在草皮脚本，不在这里
	// 详情：TurfScript

	// 未种下时，跟随鼠标
	if (mIsPlanted == false)
	{
		// 让对象附着在鼠标坐标上
		GetTransform()->SetPosition(Input::GetMousePosition());

		// 按下右键，取消种植
		if (Input::GetMouseButton(0) || Input::GetMouseButton(1))
		{
			// 植物管理器取消记录
			mPlantManager->mMouseHold = nullptr;

			// 销毁自身
			Destroy(mGameObject);
		}
	}
}

