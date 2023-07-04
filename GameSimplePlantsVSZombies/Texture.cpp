#include "Texture.h"

Texture::Texture(SDL_Texture* texture)
{
	this->sdlTexture = texture;
	// 自动获取纹理大小
	SDL_QueryTexture(texture, nullptr, nullptr, &rectRgn.w, &rectRgn.h);
}

Texture::Texture(SDL_Texture* sdlTexture, int x, int y, int w, int h)
{
	this->sdlTexture = sdlTexture;
	rectRgn = {x, y, w, h};
}

Texture::Texture(SDL_Texture* sdlTexture, const Math::rectangle_i& rgn)
{
	this->sdlTexture = sdlTexture;
	rectRgn = rgn;
}

Texture::Texture(SDL_Texture* texture, const Vector2& size):
	Texture(texture, 0, 0, (int)size.x, (int)size.y)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(sdlTexture);
	sdlTexture = nullptr;
}

void Texture::SetRectRgn(const Math::rectangle_i& rgn)
{
	
	rectRgn = rgn;
}

void Texture::SetTextureAlpha(uint8_t alpha)
{
	mAlpha = alpha;
	// 改变纹理透明度只需要设置一次即可，纹理会一直保持透明度
	//SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(sdlTexture, mAlpha);
}
