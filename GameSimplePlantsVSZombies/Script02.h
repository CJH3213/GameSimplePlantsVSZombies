#pragma once
#include "ComponentBase.h"
#include "ImageButton.h"
#include "TextButton.h"

class Script02
	: public ComponentBase
{
private:

public:
	// ��ʼð�հ�ť
	ImageButton* mBtnStart = nullptr;
	// �˳���ť
	ImageButton* mBtnExit = nullptr;

	// �ű���ʼ��
	virtual void Awake() override;
};

