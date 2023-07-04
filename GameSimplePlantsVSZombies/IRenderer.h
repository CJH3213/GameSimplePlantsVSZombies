#pragma once
#include "Window.h"

/// <summary>
/// ��Ⱦ�ӿڣ�ʵ�ָýӿڵ�������ܱ���Ⱦ�������ӹ�
/// </summary>
class IRenderer
{
public:
	// �Ƿ�����
	virtual bool IsRenderEnable() = 0;

	// ��ȡ���Ʋ㼶
	virtual int GetDrawOrder() const { return 100; }

	// ���ƽӿ�
	virtual void OnRender(Window* w) = 0;
};

