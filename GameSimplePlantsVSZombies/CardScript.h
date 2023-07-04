#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "TextureRender.h"
#include "CardBankScript.h"
#include "ChooseBoxScript.h"
#include "PlantsManager.h"
#include "CardInfo.h"

class CardScript
	: public ComponentBase
{
private:
	// 记录CD遮罩图像原始尺寸
	Vector2 mCDMaskSize;

	// 卡片银行对象
	CardBankScript* mCardBank = nullptr;
	// 选卡栏对象
	ChooseBoxScript* mChooser = nullptr;
	// 植物管理器
	PlantsManager* mPlantManager = nullptr;

	// 冷却时间计数器
	float mCDTime = 0.0f;
	// 上一帧时间
	float mTimeLast = 0.0f;

	// 设置冷却遮罩进度
	void SetCDMask(float f);

public:
	// 按钮组件
	Button* mButton = nullptr;
	// 不可用遮罩图像
	TextureRender* mDisableMask = nullptr;
	// CD遮罩图像
	TextureRender* mCDMask = nullptr;
	// 植物头像图 组件
	TextureRender* mFace = nullptr;
	// 价格文本 组件
	TextComponent* mCostText = nullptr;
	// 卡片植物信息
	CardInfo mCardInfo;

	// 预览植物对象预制件
	Prefab* mPrefabObj = nullptr;
	// 实际种植对象预制件
	Prefab* mPlantObj = nullptr;

	enum CardState
	{
		InChooser,
		IsMoving,
		InBank,
		IsLock,
	};
	// 卡片位置状态
	CardState mState = InChooser;
	// 卡片使用状态
	bool mIsUsing = true;

	// 脚本初始化
	virtual void Awake() override;
	// 帧逻辑更新
	virtual void Update() override;

	// 按键回调
	void OnClick();

	// 将卡片从 选卡栏 添加到 卡槽
	void AddCard();
	// 将卡片从 卡槽 退回到 选卡栏
	void RemoveCard();
	// 开始冷却卡牌
	void BeginCoolDown();
	// 设置卡片是否可使用
	void SetUsable(bool b);
};

