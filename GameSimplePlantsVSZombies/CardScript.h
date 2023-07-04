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
	// ��¼CD����ͼ��ԭʼ�ߴ�
	Vector2 mCDMaskSize;

	// ��Ƭ���ж���
	CardBankScript* mCardBank = nullptr;
	// ѡ��������
	ChooseBoxScript* mChooser = nullptr;
	// ֲ�������
	PlantsManager* mPlantManager = nullptr;

	// ��ȴʱ�������
	float mCDTime = 0.0f;
	// ��һ֡ʱ��
	float mTimeLast = 0.0f;

	// ������ȴ���ֽ���
	void SetCDMask(float f);

public:
	// ��ť���
	Button* mButton = nullptr;
	// ����������ͼ��
	TextureRender* mDisableMask = nullptr;
	// CD����ͼ��
	TextureRender* mCDMask = nullptr;
	// ֲ��ͷ��ͼ ���
	TextureRender* mFace = nullptr;
	// �۸��ı� ���
	TextComponent* mCostText = nullptr;
	// ��Ƭֲ����Ϣ
	CardInfo mCardInfo;

	// Ԥ��ֲ�����Ԥ�Ƽ�
	Prefab* mPrefabObj = nullptr;
	// ʵ����ֲ����Ԥ�Ƽ�
	Prefab* mPlantObj = nullptr;

	enum CardState
	{
		InChooser,
		IsMoving,
		InBank,
		IsLock,
	};
	// ��Ƭλ��״̬
	CardState mState = InChooser;
	// ��Ƭʹ��״̬
	bool mIsUsing = true;

	// �ű���ʼ��
	virtual void Awake() override;
	// ֡�߼�����
	virtual void Update() override;

	// �����ص�
	void OnClick();

	// ����Ƭ�� ѡ���� ��ӵ� ����
	void AddCard();
	// ����Ƭ�� ���� �˻ص� ѡ����
	void RemoveCard();
	// ��ʼ��ȴ����
	void BeginCoolDown();
	// ���ÿ�Ƭ�Ƿ��ʹ��
	void SetUsable(bool b);
};

