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
	// ��Ƭ����
	CardBankScript* mCardBank = nullptr;
	// ��Ƶ�������
	AudioSource* mAudio = nullptr;

	// ��������ʱ��
	float mDisappearTime = 0.0f;
	// ��ǵ�ǰ̫���Ǵ�̫������С̫��
	bool mIsBigSun = false;

	// ̫�����￨Ƭ���к�Ļص�
	void ToBankFinish();
	// ����¼��ص�
	void OnClick();

public:
	// ��ť���
	Button* mBtn = nullptr;
	// �˶��������
	Animator* mAnim = nullptr;

	// �ű���ʼ��
	virtual void Awake() override;
	// �߼�����
	virtual void Update() override;

	// ����̫����С
	void SetIsBigSun(bool b);
};

