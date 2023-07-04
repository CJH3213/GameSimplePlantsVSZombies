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
	// ��Ƭ������������Ҫ���ֲ���˳��
	std::map<std::string, class CardScript*> mCards;
	// ���Ƭ����
	const int mMaxCardNum = 6;
	// �����������
	int mSunNum = 500;

	// ��ȴ���п�Ƭ
	void CoolDownAllCards();
	// ������п�Ƭ�Ƿ������
	void CheckCardsAffordable();
	// �������
	void AddShovel();
	// ��ս��ʼ������
	void BattleBegins();

public:
	// �������
	Animator* mAnimator = nullptr;
	// ����ֵ���ı����
	TextComponent* mSunNumText = nullptr;

	// �����ʼ��
	virtual void Awake() override;

	// ��ȡ���п���
	size_t GetCardCount() const ;
	// ��ȡ��Ƭ����
	Vector2 GetCardCenterPos(int index);
	// �жϿ����Ƿ�����
	bool IsFull();
	// �ж��Ƿ�Ƭ�Ѵ���
	bool HasCardWithName(std::string name);
	// ��ӿ�Ƭ
	void AddCard(Card* card);
	// �Ƴ���Ƭ
	void RemoveCard(std::string name);
	// ��ʼ��ս
	void LetsRock();
	// �ɹ���ֲ�ص�
	void Planted(std::string name);
	// ��������ֵ�����븺�����֧����
	void AddSunNum(int num);
};

