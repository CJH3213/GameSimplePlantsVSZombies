#pragma once
#include "ComponentBase.h"
#include "TextComponent.h"
#include "GameObject.h"
// #include "CardScript.h"
#include "Card.h"
#include <map>
#include "Animator.h"

class CardBankScript
	: public ComponentBase
{
private:
	// 卡片容器（容器需要保持插入顺序）
	std::map<std::string, class CardScript*> mCards;
	// 最大卡片数量
	const int mMaxCardNum = 6;
	// 现有阳光余额
	int mSunNum = 500;

	// 冷却所有卡片
	void CoolDownAllCards();
	// 检查所有卡片是否买得起
	void CheckCardsAffordable();
	// 添加铁铲
	void AddShovel();
	// 对战开始！！！
	void BattleBegins();

public:
	// 动画组件
	Animator* mAnimator = nullptr;
	// 阳光值，文本组件
	TextComponent* mSunNumText = nullptr;

	// 组件初始化
	virtual void Awake() override;

	// 获取现有卡数
	size_t GetCardCount() const ;
	// 获取卡片坐标
	Vector2 GetCardCenterPos(int index);
	// 判断卡槽是否已满
	bool IsFull();
	// 判断是否卡片已存在
	bool HasCardWithName(std::string name);
	// 添加卡片
	void AddCard(Card* card);
	// 移除卡片
	void RemoveCard(std::string name);
	// 开始对战
	void LetsRock();
	// 成功种植回调
	void Planted(std::string name);
	// 收入阳光值（传入负数变成支出）
	void AddSunNum(int num);
};

