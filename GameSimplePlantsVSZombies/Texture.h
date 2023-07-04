#pragma once
#include <SDL.h>
#include "MathBase.h"
#include "Vector2.h"

/// <summary>
/// 对SDL的Texture类型进行抽象
/// 如果使用其他图形库，请自行实现对应方法
/// </summary>
class Texture
{
private:
	// 透明通道（默认不透明）
	uint8_t mAlpha = 0xFF;

public:
	//原纹理
	SDL_Texture* sdlTexture = nullptr;
	//裁剪范围（矩形区域，左上角起点，长宽）
	Math::rectangle_i rectRgn;

	//构造函数
	Texture(SDL_Texture* texture);
	Texture(SDL_Texture* texture, int x, int y, int w, int h);
	Texture(SDL_Texture* texture, const Math::rectangle_i& rgn);
	Texture(SDL_Texture* texture, const Vector2& size);
	//析构函数
	~Texture();

	//设置裁剪范围
	void SetRectRgn(const Math::rectangle_i& rgn);
	// 设置纹理透明度
	void SetTextureAlpha(uint8_t alpha);

	//获取纹理宽高
	inline int GetWidth() const {return rectRgn.w; }
	inline int GetHeight() const {return rectRgn.h; }
	Vector2 GetSize() const { return Vector2((float)rectRgn.w, (float)rectRgn.h); }
};

