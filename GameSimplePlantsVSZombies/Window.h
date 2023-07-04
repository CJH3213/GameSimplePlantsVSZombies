#pragma once
#include <SDL.h>
#include <string>
#include "MathBase.h"
#include "Texture.h"
#include "Vector2.h"
#include "Rectangle.h"

class Window
{
private:
	// 窗体对象
	SDL_Window* sdlWindow = nullptr;
	// 该窗体的渲染器
	SDL_Renderer* sdlRenderer = nullptr;

public:
	// 构造
	Window(std::string title, Math::rectangle_i rect);
	Window(std::string title, int w, int h);
	// 析构
	~Window();

	// 获取SDL窗体
	inline SDL_Window* GetSDLWindow() { return sdlWindow; }
	// 获取渲染器
	inline SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }

	// 设置窗体图标
	void SetIcon(std::string imgPath);
	// 获取窗体大小
	Vector2 GetSize() const;
	// 将渲染器清理为一种颜色
	void ClearByColor(int a, int r, int g, int b);
	// 将纹理复制到渲染器上
	bool CopyTextureToRenderer(Texture* texture, Vector2 const& position, float rotation, Vector2 const& scale, Math::rectangle_i* clippingRect, Vector2 const& offset, bool flipX, bool flipY);
	// 将渲染器提交到窗体
	void Present();
	// 设置渲染器渲染对象（纹理）
	bool SetRenderTarget(Texture* texture);
	// 创建为渲染目标的纹理
	Texture* CreateTextureForTarget();
	// 窗口是否为最小化状态
	bool IsMinimized();


	// 设置画笔颜色
	void SetPenColor(int a, int r, int g, int b);
	// 绘制基础几何图形：矩形
	void DrawRectangle(const Rectangle& rect);
};

