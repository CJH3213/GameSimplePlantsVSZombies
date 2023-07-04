#include "Window.h"
#include <SDL_image.h>

Window::Window(std::string title, 
	Math::rectangle_i rect)
{
	// 初始化SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//创建窗体
	sdlWindow = SDL_CreateWindow((title.c_str()),
		rect.x, rect.y, rect.w, rect.h, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	//创建渲染器（硬件加速、垂直同步）
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// 初始化图像库（适配PNG和JPG格式；没有GIF格式啊，自己做序列咯）
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	{
		SDL_Log(u8"IMG_Init错误，错误信息：%s", IMG_GetError());
	}

}

Window::Window(std::string title, int w, int h):
	Window(title, { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h })
{
}

Window::~Window()
{
	SDL_DestroyRenderer(sdlRenderer);	//销毁渲染器
	SDL_DestroyWindow(sdlWindow);		//销毁窗体
	SDL_Quit();
}

void Window::SetIcon(std::string imgPath)
{
	auto icon = IMG_Load(imgPath.c_str());
	SDL_SetWindowIcon(sdlWindow, icon);
	//delete icon;	//禁止销毁图标Surface
}

Vector2 Window::GetSize() const
{
	int Window_W, Window_H;
	SDL_GetWindowSize(sdlWindow, &Window_W, &Window_H);
	return Vector2((float)Window_W, (float)Window_H);
}

/// <summary>
/// 将渲染器清理为一种颜色
/// </summary>
/// <param name="a">透明通道</param>
/// <param name="r">红</param>
/// <param name="g">绿</param>
/// <param name="b">蓝</param>
void Window::ClearByColor(int a, int r, int g, int b)
{
	SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);	//画笔
	SDL_RenderClear(sdlRenderer);		//Clear会消耗内存，如果不及时渲染将造成内存泄漏
}

/// <summary>
/// 复制纹理到渲染器上
/// </summary>
/// <param name="texture">纹理对象</param>
/// <param name="position">屏幕坐标，即纹理左上角坐标</param>
/// <param name="rotation">旋转角度（角度制）</param>
/// <param name="scale">缩放比例</param>
/// <param name="clippingRect">裁剪原纹理区</param>
/// <param name="offset">偏移纹理，常用于将纹理中心与坐标对齐</param>
/// <param name="flipX">水平翻转</param>
/// <param name="flipY">垂直翻转</param>
/// <returns>SDL复制纹理是否成功</returns>
bool Window::CopyTextureToRenderer(Texture* texture, Vector2 const & position, float rotation, Vector2 const & scale, Math::rectangle_i* clippingRect, Vector2 const & offset, bool flipX, bool flipY)
{
	//选取原纹理部分矩形
	SDL_Rect sr;
	//如果传入选区为空，选取纹理自带截取区
	if (clippingRect == nullptr)
	{
		sr.x = texture->rectRgn.x;
		sr.y = texture->rectRgn.y;
		sr.w = texture->rectRgn.w;
		sr.h = texture->rectRgn.h;
	}
	//否则则引用传入的选区
	else
	{
		sr.x = clippingRect->x;
		sr.y = clippingRect->y;
		sr.w = clippingRect->w;
		sr.h = clippingRect->h;
	}

	//投射到窗体的矩形
	SDL_Rect dr
	{
		//屏幕坐标 - 偏移坐标
		static_cast<int>(position.x + offset.x),
		static_cast<int>(position.y + offset.y),
		//缩放
		static_cast<int>(sr.w * scale.x),
		static_cast<int>(sr.h * scale.y),
	};

	//翻转属性
	int flip = SDL_FLIP_NONE;
	if (flipX)
		flip = SDL_FLIP_HORIZONTAL;
	if(flipY)
		flip |= SDL_FLIP_VERTICAL;

	//复制纹理到渲染器
	int res = -1;
	res = SDL_RenderCopyEx(sdlRenderer, texture->sdlTexture,
		&sr, &dr,					//原选取部分、画布选取部分
		rotation, nullptr,			//旋转角、旋转中心点
		SDL_RendererFlip( flip));	//翻转
	
	//复制成功返回true
	return res == 0 ? true : false;
}

void Window::Present()
{
	//交换缓冲区；该功能不能屏蔽，否则渲染数据无法提交到显卡，占用巨量内存
	//完成最基本的显示功能仅需19MB！！请注意内存消耗。
	SDL_RenderPresent(sdlRenderer);
}

/// <summary>
/// 设置渲染器渲染对象（纹理）
/// </summary>
/// <param name="texture">渲染的纹理对象，如果空指针则渲染对象为窗口</param>
/// <returns>成功、失败</returns>
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
	SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);	//画笔
}

void Window::DrawRectangle(const Rectangle& rect)
{
	Vector2 topLeft = rect.GetTopLeftPoint();
	const SDL_FRect frect = { topLeft.x, topLeft.y, rect.mSize.x, rect.mSize.y };
	SDL_RenderDrawRectF(sdlRenderer, &frect);
}
