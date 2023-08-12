#pragma once
#include "ComponentBase.h"
#include "Button.h"
#include "CardBankScript.h"
#include "Animator.h"
#include "AudioSource.h"

class SunScript :
	public ComponentBase
{
private:
	// 卡片银行
	CardBankScript* mCardBank = nullptr;
	// 音频组件引用
	AudioSource* mAudio = nullptr;

	// 阳光销毁时间
	float mDisappearTime = 0.0f;
	// 标记当前太阳是大太阳还是小太阳
	bool mIsBigSun = false;

	// 太阳到达卡片银行后的回调
	void ToBankFinish();
	// 点击事件回调
	void OnClick();

public:
	// 按钮组件
	Button* mBtn = nullptr;
	// 运动动画组件
	Animator* mAnim = nullptr;

	// 脚本初始化
	virtual void Awake() override;
	// 逻辑更新
	virtual void Update() override;

	// 设置太阳大小
	void SetIsBigSun(bool b);
};

