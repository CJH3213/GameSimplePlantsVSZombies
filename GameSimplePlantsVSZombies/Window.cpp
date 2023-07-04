#include "Window.h"
#include <SDL_image.h>

Window::Window(std::string title, 
	Math::rectangle_i rect)
{
	// ��ʼ��SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//��������
	sdlWindow = SDL_CreateWindow((title.c_str()),
		rect.x, rect.y, rect.w, rect.h, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	//������Ⱦ����Ӳ�����١���ֱͬ����
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// ��ʼ��ͼ��⣨����PNG��JPG��ʽ��û��GIF��ʽ�����Լ������п���
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	{
		SDL_Log(u8"IMG_Init���󣬴�����Ϣ��%s", IMG_GetError());
	}

}

Window::Window(std::string title, int w, int h):
	Window(title, { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h })
{
}

Window::~Window()
{
	SDL_DestroyRenderer(sdlRenderer);	//������Ⱦ��
	SDL_DestroyWindow(sdlWindow);		//���ٴ���
	SDL_Quit();
}

void Window::SetIcon(std::string imgPath)
{
	auto icon = IMG_Load(imgPath.c_str());
	SDL_SetWindowIcon(sdlWindow, icon);
	//delete icon;	//��ֹ����ͼ��Surface
}

Vector2 Window::GetSize() const
{
	int Window_W, Window_H;
	SDL_GetWindowSize(sdlWindow, &Window_W, &Window_H);
	return Vector2((float)Window_W, (float)Window_H);
}

/// <summary>
/// ����Ⱦ������Ϊһ����ɫ
/// </summary>
/// <param name="a">͸��ͨ��</param>
/// <param name="r">��</param>
/// <param name="g">��</param>
/// <param name="b">��</param>
void Window::ClearByColor(int a, int r, int g, int b)
{
	SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);	//����
	SDL_RenderClear(sdlRenderer);		//Clear�������ڴ棬�������ʱ��Ⱦ������ڴ�й©
}

/// <summary>
/// ����������Ⱦ����
/// </summary>
/// <param name="texture">�������</param>
/// <param name="position">��Ļ���꣬���������Ͻ�����</param>
/// <param name="rotation">��ת�Ƕȣ��Ƕ��ƣ�</param>
/// <param name="scale">���ű���</param>
/// <param name="clippingRect">�ü�ԭ������</param>
/// <param name="offset">ƫ�����������ڽ������������������</param>
/// <param name="flipX">ˮƽ��ת</param>
/// <param name="flipY">��ֱ��ת</param>
/// <returns>SDL���������Ƿ�ɹ�</returns>
bool Window::CopyTextureToRenderer(Texture* texture, Vector2 const & position, float rotation, Vector2 const & scale, Math::rectangle_i* clippingRect, Vector2 const & offset, bool flipX, bool flipY)
{
	//ѡȡԭ�����־���
	SDL_Rect sr;
	//�������ѡ��Ϊ�գ�ѡȡ�����Դ���ȡ��
	if (clippingRect == nullptr)
	{
		sr.x = texture->rectRgn.x;
		sr.y = texture->rectRgn.y;
		sr.w = texture->rectRgn.w;
		sr.h = texture->rectRgn.h;
	}
	//���������ô����ѡ��
	else
	{
		sr.x = clippingRect->x;
		sr.y = clippingRect->y;
		sr.w = clippingRect->w;
		sr.h = clippingRect->h;
	}

	//Ͷ�䵽����ľ���
	SDL_Rect dr
	{
		//��Ļ���� - ƫ������
		static_cast<int>(position.x + offset.x),
		static_cast<int>(position.y + offset.y),
		//����
		static_cast<int>(sr.w * scale.x),
		static_cast<int>(sr.h * scale.y),
	};

	//��ת����
	int flip = SDL_FLIP_NONE;
	if (flipX)
		flip = SDL_FLIP_HORIZONTAL;
	if(flipY)
		flip |= SDL_FLIP_VERTICAL;

	//����������Ⱦ��
	int res = -1;
	res = SDL_RenderCopyEx(sdlRenderer, texture->sdlTexture,
		&sr, &dr,					//ԭѡȡ���֡�����ѡȡ����
		rotation, nullptr,			//��ת�ǡ���ת���ĵ�
		SDL_RendererFlip( flip));	//��ת
	
	//���Ƴɹ�����true
	return res == 0 ? true : false;
}

void Window::Present()
{
	//�������������ù��ܲ������Σ�������Ⱦ�����޷��ύ���Կ���ռ�þ����ڴ�
	//������������ʾ���ܽ���19MB������ע���ڴ����ġ�
	SDL_RenderPresent(sdlRenderer);
}

/// <summary>
/// ������Ⱦ����Ⱦ��������
/// </summary>
/// <param name="texture">��Ⱦ��������������ָ������Ⱦ����Ϊ����</param>
/// <returns>�ɹ���ʧ��</returns>
bool Window::SetRenderTarget(Texture* texture)
{
	SDL_Texture* sdlTexture = texture ? texture->sdlTexture : nullptr;
	int res = SDL_SetRenderTarget(sdlRenderer, sdlTexture);
	return res == 0 ? true  : false;
}

Texture* Window::CreateTextureForTarget()
{
	Vector2 winSize = GetSize();
	SDL_Texture* sdlTexture  = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int)winSize.x, (int)winSize.y);
	if (sdlTexture)
		return new Texture(sdlTexture, winSize);
	else
	return nullptr;
}

bool Window::IsMinimized()
{
	if (SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_MINIMIZED)
		return true;
	else
		return false;
}

void Window::SetPenColor(int a, int r, int g, int b)
{
	SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);	//����
}

void Window::DrawRectangle(const Rectangle& rect)
{
	Vector2 topLeft = rect.GetTopLeftPoint();
	const SDL_FRect frect = { topLeft.x, topLeft.y, rect.mSize.x, rect.mSize.y };
	SDL_RenderDrawRectF(sdlRenderer, &frect);
}
