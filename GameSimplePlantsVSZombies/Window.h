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
	// �������
	SDL_Window* sdlWindow = nullptr;
	// �ô������Ⱦ��
	SDL_Renderer* sdlRenderer = nullptr;

public:
	// ����
	Window(std::string title, Math::rectangle_i rect);
	Window(std::string title, int w, int h);
	// ����
	~Window();

	// ��ȡSDL����
	inline SDL_Window* GetSDLWindow() { return sdlWindow; }
	// ��ȡ��Ⱦ��
	inline SDL_Renderer* GetSDLRenderer() { return sdlRenderer; }

	// ���ô���ͼ��
	void SetIcon(std::string imgPath);
	// ��ȡ�����С
	Vector2 GetSize() const;
	// ����Ⱦ������Ϊһ����ɫ
	void ClearByColor(int a, int r, int g, int b);
	// �������Ƶ���Ⱦ����
	bool CopyTextureToRenderer(Texture* texture, Vector2 const& position, float rotation, Vector2 const& scale, Math::rectangle_i* clippingRect, Vector2 const& offset, bool flipX, bool flipY);
	// ����Ⱦ���ύ������
	void Present();
	// ������Ⱦ����Ⱦ��������
	bool SetRenderTarget(Texture* texture);
	// ����Ϊ��ȾĿ�������
	Texture* CreateTextureForTarget();
	// �����Ƿ�Ϊ��С��״̬
	bool IsMinimized();


	// ���û�����ɫ
	void SetPenColor(int a, int r, int g, int b);
	// ���ƻ�������ͼ�Σ�����
	void DrawRectangle(const Rectangle& rect);
};

