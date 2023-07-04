#pragma once
#include "ComponentBase.h"
#include <map>
#include "Card.h"
#include "CardBankScript.h"
#include "ImageButton.h"
#include "LevelBackGround.h"
#include "CardInfo.h"
#include "AudioSource.h"

class ChooseBoxScript
	: public ComponentBase
{
private:
	// 所有卡片角色
	std::map<std::string, Card*> mCards;

	// 卡片银行对象
	CardBankScript* mCardBank = nullptr;
	// 背景图对象
	GameObject* mBackGround = nullptr;

	// 临时写的，植物卡片信息
	std::vector<CardInfo> mCardInfo;

public:
	// “一起摇滚”按钮组件
	ImageButton* mStartBtn = nullptr;
	// 音源组件
	AudioSource* mAudio = nullptr;

	// 析构函数
	~ChooseBoxScript();

	// 组件初始化
	virtual void Awake() override;
	// 归还卡片
	void GiveBack(std::string name);

	// 点击按钮监听回调
	void OnClick();
};

