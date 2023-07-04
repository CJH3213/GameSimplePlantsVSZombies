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
	// ���п�Ƭ��ɫ
	std::map<std::string, Card*> mCards;

	// ��Ƭ���ж���
	CardBankScript* mCardBank = nullptr;
	// ����ͼ����
	GameObject* mBackGround = nullptr;

	// ��ʱд�ģ�ֲ�￨Ƭ��Ϣ
	std::vector<CardInfo> mCardInfo;

public:
	// ��һ��ҡ������ť���
	ImageButton* mStartBtn = nullptr;
	// ��Դ���
	AudioSource* mAudio = nullptr;

	// ��������
	~ChooseBoxScript();

	// �����ʼ��
	virtual void Awake() override;
	// �黹��Ƭ
	void GiveBack(std::string name);

	// �����ť�����ص�
	void OnClick();
};

