#pragma once
#include "Window.h"

/// <summary>
/// 渲染接口，实现该接口的组件才能被渲染管理器接管
/// </summary>
class IRenderer
{
public:
	// 是否启用
	virtual bool IsRenderEnable() = 0;

	// 获取绘制层级
	virtual int GetDrawOrder() const { return 100; }

	// 绘制接口
	virtual void OnRender(Window* w) = 0;
};

