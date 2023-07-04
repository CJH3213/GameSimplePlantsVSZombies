#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "PlantsManager.h"
#include "CardBankScript.h"

class TurfScript :
	public ComponentBase
{
private:
	// 卡片银行
	CardBankScript* mCardBank = nullptr;
	// 植物管理器
	PlantsManager* mPlantManager = nullptr;
	// 预种植效果对象
	GameObject* mPreviewPlant = nullptr;
	// 已种植植物对象
	GameObject* mPlant = nullptr;
	// 以后还有南瓜等植物，需要辅助的植物对象容器

public:
	// 按钮组件
	Button* mBtn = nullptr;

	// 深拷贝
	virtual ComponentBase* Clone() const override;

	// 脚本初始化
	virtual void Awake() override;

	// 销毁植物
	void DestroyPlant();

	// 鼠标移入
	void OnMouseEnter();
	// 鼠标悬空
	void OnMouseOver();
	// 鼠标移出
	void OnMouseExit();
	// 点击回调
	void OnClick();
};

